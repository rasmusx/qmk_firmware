/* Copyright 2017 Jun Wako <wakojun@gmail.com>
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
#ifndef FC660C_H
#define FC660C_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"

// Timer resolution check
#if (1000000/TIMER_RAW_FREQ > 20)
#   error "Timer resolution(>20us) is not enough for HHKB matrix scan tweak on V-USB."
#endif

/*
 * Pin configuration for ATMega32U4
 *
 * Row:     PD4-6, 7(~EN)
 * Col:     PB0-2, 3(Z5 ~EN), 4(Z4 ~EN)
 * Key:     PC6(pull-uped)
 * Hys:     PC7
 */
static inline void KEY_ENABLE(void) { (PORTD &= ~(1<<7)); }
static inline void KEY_UNABLE(void) { (PORTD |=  (1<<7)); }
static inline bool KEY_STATE(void) { return (PINC & (1<<6)); }
static inline void KEY_HYS_ON(void) { (PORTC |=  (1<<7)); }
static inline void KEY_HYS_OFF(void) { (PORTC &= ~(1<<7)); }
static inline void KEY_INIT(void) {
    /* Col */
    DDRB  |=  0x1F;
    /* Key: input with pull-up */
    DDRC  &= ~(1<<6);
    PORTC |=  (1<<6);
    /* Hys */
    DDRC  |=  (1<<7);
    /* Row */
    DDRD  |=  0xF0;

    KEY_UNABLE();
    KEY_HYS_OFF();
}

static inline void SET_ROW(uint8_t ROW) {
    // set row with unabling key
    PORTD = (PORTD & 0x0F) | (1<<7) | ((ROW & 0x07) << 4);
}

static inline void SET_COL(uint8_t COL) {
    //         |PB3(Z5 ~EN)|PB4(Z4 ~EN)
    // --------|-----------|-----------
    // Col:0-7 |high       |low
    // Col:8-F |low        |high
    PORTB = (PORTB & 0xE0) | ((COL & 0x08) ? 1<<4 : 1<<3) | (COL & 0x07);
}

#define KEYMAP( \
    K13, K10, K11, K12, K14, K16, K17, K15, K1B, K18, K19, K1A, K1C, K1E,      K1F, \
    K03, K00, K01, K02, K04, K06, K07, K05, K0B, K08, K09, K0A, K0C, K0E,      K0F, \
    K43, K40, K41, K42, K44, K46, K47, K45, K4B, K48, K49, K4A,      K4E,           \
    K33, K31, K32, K34, K36, K37, K35, K3B, K38, K39, K3A,           K3C, K3D,      \
    K23, K21, K22,                K27,                K28, K2A, K2C, K2E, K2D, K2F  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07,   \
      K08, K09, K0A, K0B, K0C, KC_NO,    K0E, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17,   \
      K18, K19, K1A, K1B, K1C, KC_NO,    K1E, K1F }, \
    { KC_NO,    K21, K22, K23, KC_NO,    KC_NO,    KC_NO,    K27,   \
      K28, KC_NO,    K2A, KC_NO,    K2C, K2D, K2E, K2F }, \
    { KC_NO,    K31, K32, K33, K34, K35, K36, K37,   \
      K38, K39, K3A, K3B, K3C, K3D, KC_NO,    KC_NO    }, \
    { K40, K41, K42, K43, K44, K45, K46, K47,   \
      K48, K49, K4A, K4B, KC_NO,    KC_NO,    K4E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      \
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      \
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      \
      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }  \
}

#endif
