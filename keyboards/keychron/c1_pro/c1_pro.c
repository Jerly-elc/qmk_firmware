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
#include "keychron_common.h"
#include "keychron_ft_common.h"


#define IO_DELAY_US    20

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
  watchdog parameter configuration
*/
static const WDGConfig wdgcfg = {
  .pr           = 3,
  .rlr          = 200,

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

void keyboard_post_init_kb(void) {
    setPinOutputPushPull(LED_MAC_OS_PIN);
    setPinOutputPushPull(LED_WIN_OS_PIN);
	setPinOutputPushPull(LED_CAPS_LOCK_PIN);
    writePin(LED_MAC_OS_PIN,    !LED_OS_PIN_ON_STATE);
    writePin(LED_WIN_OS_PIN,    !LED_OS_PIN_ON_STATE);
    writePin(LED_CAPS_LOCK_PIN, !LED_OS_PIN_ON_STATE);

    keyboard_post_init_user();

	wdgStart(&WDGD1, &wdgcfg);
}

void suspend_power_down_kb(void) {
    writePin(LED_MAC_OS_PIN,    !LED_OS_PIN_ON_STATE);
    writePin(LED_WIN_OS_PIN,    !LED_OS_PIN_ON_STATE);
    writePin(LED_CAPS_LOCK_PIN, !LED_OS_PIN_ON_STATE);
    suspend_power_down_user();
}

// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron(keycode, record)) {
        return false;
    }
    if (!process_record_keychron_ft(keycode, record)) {
        return false;
    }
    return true;
}

void housekeeping_task_user(void) {
    housekeeping_task_keychron();
    housekeeping_task_keychron_ft();
	wdgReset(&WDGD1);
}



#endif // DIP_SWITCH_ENABLE
