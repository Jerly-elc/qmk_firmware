/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

#define IO_DELAY_US    65

#define SYSTEM_TIME_CHANGE 3000
#define POWER_ON_LED_DURATION 3000

static uint32_t power_on_indicator_timer;
static uint32_t win_lock_state=0;
static uint32_t win_lock_timer=0;
static uint32_t win_timer = 0;
static bool nkro_state = 0;




// clang-format off

const matrix_row_t matrix_mask[] = {
    0b11111111111111111,
    0b11111111111111111,
    0b11111111111111111,
    0b11111111111111111,
    0b11111111111111111,
    0b11111111111011111,
};

/**
 * wait for all Row signals to go HIGH
 */
void matrix_io_delay(void) {
   uint16_t delayCnt = 0;
   for(delayCnt = 0; delayCnt < IO_DELAY_US; delayCnt++)
   {
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");
       asm volatile("nop" ::: "memory");       
   }
}

void eeconfig_init_kb(void) {
#if (EECONFIG_KB_DATA_SIZE) == 0
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);
#endif
    keymap_config.raw  = eeconfig_read_keymap();
    keymap_config.nkro = 0;
    eeconfig_update_keymap(keymap_config.raw);

    eeconfig_init_user();
}

// clang-format on

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? 0 : 2));
    }
    return true;
}

void keyboard_post_init_user_winlock(void) {
    // 初始化指示灯引脚为输出模式
    setPinOutputPushPull(WIN_LOCK_LED_PIN);
}

void suspend_power_down_user(void) {
    // 当电脑进入挂起模式时，熄灭指示灯
    writePin(WIN_LOCK_LED_PIN,  0);
}

void suspend_wakeup_init_user(void) {
    // 当电脑从挂起模式唤醒时，点亮指示灯
//    writePin(WIN_LOCK_LED_PIN,  0);
	    if (keymap_config.swap_rctl_rgui) {
			writePin(WIN_LOCK_LED_PIN,  1);
        } else{
			writePin(WIN_LOCK_LED_PIN,  0);
        }
}



void keyboard_post_init_kb(void) {
    power_on_indicator_timer = timer_read32();
	nkro_state = keymap_config.nkro;
	setPinOutputPushPull(LED_NUM_LOCK_PIN);
	setPinOutputPushPull(LED_CAPS_LOCK_PIN);
	setPinOutputPushPull(WIN_LOCK_LED_PIN);
	
    writePin(LED_NUM_LOCK_PIN,  !LED_OS_PIN_ON_STATE);	
    writePin(LED_CAPS_LOCK_PIN, !LED_OS_PIN_ON_STATE);
	writePin(WIN_LOCK_LED_PIN,  !LED_WINLOCK_PIN_ON_STATE);
    
    keyboard_post_init_user();
	suspend_power_down_user();
}

void suspend_power_down_kb(void) {
    writePin(LED_NUM_LOCK_PIN,  !LED_OS_PIN_ON_STATE);
    writePin(LED_CAPS_LOCK_PIN, !LED_OS_PIN_ON_STATE);
    writePin(WIN_LOCK_LED_PIN,  !LED_WINLOCK_PIN_ON_STATE);
}



bool keychron_task(void){
if(power_on_indicator_timer){
        if(timer_elapsed32(power_on_indicator_timer)> POWER_ON_LED_DURATION){
            power_on_indicator_timer=0;
             if (!host_keyboard_led_state().caps_lock)  writePin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
              if (!host_keyboard_led_state().num_lock)  writePin(LED_NUM_LOCK_PIN, !LED_PIN_ON_STATE);
        
        }else{
             writePin(LED_CAPS_LOCK_PIN, LED_PIN_ON_STATE);
             writePin(LED_NUM_LOCK_PIN, LED_PIN_ON_STATE);
        }
    }
    return true;
}



void gui_toggle(void) {
    keymap_config.no_gui = !keymap_config.no_gui;
    eeconfig_update_keymap(keymap_config.raw);
    led_update_kb(host_keyboard_led_state());
}

void nfro_led_flash(void)
{   
	static uint8_t rgb_flash_cnt = 0;
	static uint32_t nkro_flash_timer = 0;
	static uint8_t before_rgb_state = 0;
	if(nkro_state != keymap_config.nkro)
	{
         nkro_flash_timer = timer_read32();
		 rgb_flash_cnt = 6;
		 nkro_state = keymap_config.nkro;
		 if (!rgb_matrix_is_enabled()) {
			before_rgb_state = 0;
            rgb_matrix_enable();
         }
		 else
		 {
            before_rgb_state = 1;
		 }
	}
	if(rgb_flash_cnt > 0)
	{
	    if(timer_elapsed32(nkro_flash_timer) > 500)
	    {
		   nkro_flash_timer = timer_read32();
           rgb_flash_cnt--;
		   if(rgb_flash_cnt == 0)
		   	{
               if(before_rgb_state == 0)
               	{
                    rgb_matrix_disable();
               	}
		   	}
	    }
		if(rgb_flash_cnt % 2)
	    {
	       rgb_matrix_set_color_all(255,0,0);
	    }
		else
		{
           rgb_matrix_set_color_all(0,0,0);
		}

	}
	

	
}

void housekeeping_task_kb(void) 
{
	if (win_lock_timer) {
        if (keymap_config.no_gui) 
		{
            win_lock_timer = 0;
            gui_toggle();
        }		
        else if (timer_elapsed32(win_lock_timer) > 3000) 
		{
            win_lock_timer = 0;
            gui_toggle();
        }
    }
	if(keymap_config.no_gui){
		    rgb_matrix_set_color(WIN_LOCK_INDEX, 0,0,0);
            writePin(WIN_LOCK_LED_PIN,LED_OS_PIN_ON_STATE);
    } else {
            writePin(WIN_LOCK_LED_PIN,!LED_OS_PIN_ON_STATE);      
    }
	nfro_led_flash();
	keychron_task();

}





bool process_record_kb(uint16_t keycode, keyrecord_t *record) 
{
  if (!process_record_user(keycode, record)) 
  	{
        return false;
    }
    win_timer =timer_read32();
    switch (keycode)
		{
          case GU_TOGG:
			  if (record->event.pressed) 
			  {
				  win_lock_timer =timer_read32();
				  win_timer =timer_read32();
			   }
			   else
			   {
				   win_lock_timer=0;
				  if(timer_elapsed32(win_timer) > SYSTEM_TIME_CHANGE)
			      {
					  win_lock_state=1;
				  }else{
					   win_lock_state=0;
				  }
				  //win_lock_state = !win_lock_state;
				  eeconfig_update_user_datablock(&win_lock_state);
				   
			   }
			  return false;

		  default:return true;
    	}
	
	return true;
}



#endif // DIP_SWITCH_ENABLE
