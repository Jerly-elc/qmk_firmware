/* Copyright 2023 @ Keychron(https://www.keychron.com)
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

#pragma once

#define EECONFIG_KB_DATA_SIZE 1
#define EECONFIG_USER_DATA_SIZE 1


/* DIP switch */
//#define DIP_SWITCH_MATRIX_GRID { { 5, 4 } }
#define DIP_SWITCH_PINS { B1 }


/* Disable DIP switch in matrix data */
//#define MATRIX_MASKED

/* EEPROM Driver Configuration */
#define WEAR_LEVELING_LOGICAL_SIZE 2048
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)

/* System indication led */
#define LED_NUM_LOCK_PIN            C5
#define WIN_LOCK_LED_PIN            C1

#define LED_CAPS_LOCK_PIN           C0
#define LED_OS_PIN_ON_STATE         1
#define LED_PIN_ON_STATE            1
#define LED_WINLOCK_PIN_ON_STATE    1
#define WIN_LOCK_INDEX              88



#ifdef RGB_MATRIX_ENABLE

#    define RGB_MATRIX_SNLED27351_SPI

#    define SPI_SCK_PIN  A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7

#    define DRIVER_CS_PINS \
        { C11, C6 }

#    define SNLED23751_SPI_DIVISOR 64



#endif
/* Factory test keys */
#define FN_KEY1 MO(1)
#define FN_KEY2 MO(3)

/* Old default behavior of mod-taps */
#define HOLD_ON_OTHER_KEY_PRESS

