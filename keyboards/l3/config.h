/*
Copyright 2017 Rasmus Schults <rasmusx@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1338
#define DEVICE_VER      0x0100
#define MANUFACTURER    LeeKu
#define PRODUCT         L3
#define DESCRIPTION     tmk firmware for L3

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 20

//#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5

/* number of backlight levels */
#define BACKLIGHT_LEVELS 1

/* key combination for magic key command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#define RGB_LEDS_NOT_SOLDERED
//#define RGBLIGHT_ANIMATIONS
//#define RGB_DI_PIN D6
//#define RGBLED_NUM 17

#define I2C_BITRATE_KHZ 400
#define I2C_TARGET_ADDR 0xB0

#endif
