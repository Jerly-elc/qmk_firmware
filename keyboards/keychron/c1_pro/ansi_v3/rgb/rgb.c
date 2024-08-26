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

// clang-format off
#ifdef RGB_MATRIX_ENABLE  
const snled27351_led_t PROGMEM g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {  
/* Refer to snled27351 manual for these locations  
 *   driver  
 *   |  R location  
 *   |  |       G location  
 *   |  |       |       B location  
 *   |  |       |       | */  

    {0, G_16,  I_16,  H_16},  
    {0, G_14,  I_14,  H_14},  
    {0, G_13,  I_13,  H_13},  
    {0, G_12,  I_12,  H_12},  
    {0, G_11,  I_11,  H_11},  
    {0, G_10,  I_10,  H_10},  
    {0, G_9,   I_9,   H_9 },  
    {0, G_8,   I_8,   H_8 },  
    {0, G_7,   I_7,   H_7 },  
    {0, G_6,   I_6,   H_6 },  
    {0, G_5,   I_5,   H_5 },  
    {0, G_4,   I_4,   H_4 },  
    {0, G_3,   I_3,   H_3 },  
    {0, G_2,   I_2,   H_2 },  
    {0, G_1,   I_1,   H_1 },  
    {1, A_4,   C_4,   B_4 },  

    {0, A_16,  C_16,  B_16},  
    {0, A_15,  C_15,  B_15},  
    {0, A_14,  C_14,  B_14},  
    {0, A_13,  C_13,  B_13},  
    {0, A_12,  C_12,  B_12},  
    {0, A_11,  C_11,  B_11},  
    {0, A_10,  C_10,  B_10},  
    {0, A_9,   C_9,   B_9},  
    {0, A_8,   C_8,   B_8},  
    {0, A_7,   C_7,   B_7},  
    {0, A_6,   C_6,   B_6},  
    {0, A_5,   C_5,   B_5},  
    {0, A_4,   C_4,   B_4},  
    {0, A_3,   C_3,   B_3},  
    {0, A_2,   C_2,   B_2},  
    {0, A_1,   C_1,   B_1},  
    {1, A_1,   C_1,   B_1},  

    {0, D_16,  F_16,  E_16},  
    {0, D_15,  F_15,  E_15},  
    {0, D_14,  F_14,  E_14},  
    {0, D_13,  F_13,  E_13},  
    {0, D_12,  F_12,  E_12},  
    {0, D_11,  F_11,  E_11},  
    {0, D_10,  F_10,  E_10},  
    {0, D_9,   F_9,   E_9 },  
    {0, D_8,   F_8,   E_8 },  
    {0, D_7,   F_7,   E_7 },  
    {0, D_6,   F_6,   E_6 },  
    {0, D_5,   F_5,   E_5 },  
    {0, D_4,   F_4,   E_4 },  
    {0, D_3,   F_3,   E_3 },  
    {0, D_2,   F_2,   E_2 },  
    {0, D_1,   F_1,   E_1 },  
    {1, A_2,   C_2,   B_2 },  

    {1, A_16,  C_16,  B_16},  
    {1, A_15,  C_15,  B_15},  
    {1, A_14,  C_14,  B_14},  
    {1, A_13,  C_13,  B_13},  
    {1, A_12,  C_12,  B_12},  
    {1, A_11,  C_11,  B_11},  
    {1, A_10,  C_10,  B_10},  
    {1, A_9,   C_9,   B_9},  
    {1, A_8,   C_8,   B_8},  
    {1, A_7,   C_7,   B_7},  
    {1, A_6,   C_6,   B_6},  
    {1, A_5,   C_5,   B_5},  
    {1, A_3,   C_3,   B_3},  

    {1, G_16,  I_16,  H_16},  
    
    {1, G_14,  I_14,  H_14},  
    {1, G_13,  I_13,  H_13},  
    {1, G_12,  I_12,  H_12},  
    {1, G_11,  I_11,  H_11},  
    {1, G_10,  I_10,  H_10},  
    {1, G_9,   I_9,   H_9 },  
    {1, G_8,   I_8,   H_8 },  
    {1, G_7,   I_7,   H_7 },  
    {1, G_6,   I_6,   H_6 },  
    {1, G_5,   I_5,   H_5 },  
    {1, G_3,   I_3,   H_3 },  
    {1, G_1,   I_1,   H_1 },  

    {1, D_16,  F_16,  E_16},  
    {1, D_15,  F_15,  E_15},  
    {1, D_14,  F_14,  E_14},  
    {1, D_10,  F_10,  E_10},  
    {1, D_6,   F_6,   E_6 },  
    {1, D_5,   F_5,   E_5 },  
    {1, D_4,   F_4,   E_4 },  
    {1, D_3,   F_3,   E_3 },  
    {1, D_2,   F_2,   E_2 },  
    {1, D_1,   F_1,   E_1 },  
    {1, G_2,   I_2,   H_2 },  
};  



// clang-format on
#if 0
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_enable();
            }
            return false;
    }
    return true;
}
#endif
void housekeeping_task_kb(void) {
    if (default_layer_state == (1 << 0)) {
        writePin(LED_MAC_OS_PIN, LED_OS_PIN_ON_STATE);
        writePin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
    }
    if (default_layer_state == (1 << 2)) {
        writePin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
        writePin(LED_WIN_OS_PIN, LED_OS_PIN_ON_STATE);
    }
}


#endif
