/* Copyright 2017 Rasmus Schults <rasmusx@gmail.com>
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
#include "fc660c.h"

enum macro_id {
  SHRUG,
  FAST,
  FLIP,
};

#define TYPE_FLIP MACRO( \
  T(ENT), D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0),  T(0),  T(2),  T(8), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(2),  T(5),  T(6),  T(F), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0),  T(0),  T(B),  T(0), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(2),  T(5),  T(A),  T(1), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0),  T(0),  T(B),  T(0), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(F),  T(F),  T(0),  T(9), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(2),  T(5),  T(6),  T(F), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(F),  T(E),  T(3),  T(5), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0),  T(0),  T(2),  T(0), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(2),  T(5),  T(3),  T(B), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(2),  T(5),  T(0),  T(1), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(2),  T(5),  T(3),  T(B), \
  T(SPACE), T(ENT), END \
)

#define TYPE_SHRUG MACRO( \
  I(0), T(ENT), D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0), T(0), T(A), T(F), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0), T(0), T(5), T(C), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0), T(0), T(5), T(F), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0), T(0), T(2), T(8), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(3), T(0), T(C), T(4), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0), T(0), T(2), T(9), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0), T(0), T(5), T(F), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0), T(0), T(2), T(F), \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
  T(0), T(0), T(A), T(F), \
  T(SPACE), T(ENT), END \
)

#define M_SHRUG M(SHRUG)

enum custom_keycodes {
    TESTING = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP(
    KC_GESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,        KC_INS,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,        KC_DEL,
    KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,        KC_ENT,
    KC_LSPO,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,                KC_RSPC,KC_UP,
    KC_LCTL,KC_LALT,KC_LGUI,                KC_SPC,                                 KC_RGUI,KC_RCTL,MO(2),  KC_LEFT,KC_DOWN,KC_RGHT
),
[1] = KEYMAP(
    KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,        KC_INS,
    KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,        KC_DEL,
    KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,        KC_ENT,
    KC_LSPO,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,                KC_RSPC,KC_UP,
    KC_LCTL,KC_LGUI,KC_LALT,                KC_SPC,                                 KC_RALT,KC_RCTL,MO(2),  KC_LEFT,KC_DOWN,KC_RGHT
),
[2] = KEYMAP(
    KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_TRNS,        M(SHRUG),
    KC_TRNS,TG(1),  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PSCR,KC_SLCK,KC_PAUS,KC_TRNS,KC_TRNS,KC_TRNS,        TESTING,
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_HOME,KC_PGUP,KC_TRNS,KC_TRNS,        KC_TRNS,
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_END ,KC_PGDN,KC_TRNS,                KC_TRNS,KC_PGUP,
    KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,                                KC_TRNS,KC_TRNS,MO(2),  KC_HOME,KC_PGDN,KC_END
)};

const uint16_t PROGMEM fn_actions[] = {};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
        case SHRUG:
            return (record->event.pressed ? TYPE_SHRUG : MACRO_NONE );
        case FLIP:
            return (record->event.pressed ? TYPE_FLIP : MACRO_NONE );
        case FAST:
            return (record->event.pressed ? MACRO(T(ENT), T(T), T(E), T(S), T(T), W(255), T(T), T(E), T(S), T(T), T(T), T(E), T(S), T(T), T(ENT), END ) : MACRO_NONE );
    }
    return MACRO_NONE;
};

uint8_t key2asc(uint8_t key)
{
    switch (key) {
        case KC_A: return 'a';
        case KC_B: return 'b';
        case KC_C: return 'c';
        case KC_D: return 'd';
        case KC_E: return 'e';
        case KC_F: return 'f';
        case KC_G: return 'g';
        case KC_H: return 'h';
        case KC_I: return 'i';
        case KC_J: return 'j';
        case KC_K: return 'k';
        case KC_L: return 'l';
        case KC_M: return 'm';
        case KC_N: return 'n';
        case KC_O: return 'o';
        case KC_P: return 'p';
        case KC_Q: return 'q';
        case KC_R: return 'r';
        case KC_S: return 's';
        case KC_T: return 't';
        case KC_U: return 'u';
        case KC_V: return 'v';
        case KC_W: return 'w';
        case KC_X: return 'x';
        case KC_Y: return 'y';
        case KC_Z: return 'z';
        case KC_1: return '1';
        case KC_2: return '2';
        case KC_3: return '3';
        case KC_4: return '4';
        case KC_5: return '5';
        case KC_6: return '6';
        case KC_7: return '7';
        case KC_8: return '8';
        case KC_9: return '9';
        case KC_0: return '0';
        case KC_ENTER: return '\n';
        case KC_ESCAPE: return 0x1B;
        case KC_BSPACE: return '\b';
        case KC_TAB: return '\t';
        case KC_SPACE: return ' ';
        case KC_MINUS: return '-';
        case KC_EQUAL: return '=';
        case KC_LBRACKET: return '[';
        case KC_RBRACKET: return ']';
        case KC_BSLASH: return '\\';
        case KC_NONUS_HASH: return '\\';
        case KC_SCOLON: return ';';
        case KC_QUOTE: return '\'';
        case KC_GRAVE: return '`';
        case KC_COMMA: return ',';
        case KC_DOT: return '.';
        case KC_SLASH: return '/';
        default: return 0x00;
    }
}

struct Stack {
  char T[10];
  char Z[10];
  char Y[10];
  char X[10];
};

struct Stack stack;

bool calculator = false;
char val[1];
float x,y;
bool calcdone = false;

#include <ctype.h>
#include <stdlib.h>

char output[50];

void print_stack(void) {
  xprintf("\n STACK --- x:%s y:%s z:%s t: %s\n",stack.X, stack.Y, stack.Z, stack.T);
}

void calc_on(void) {
  calculator = true;
}

void calc_off(void) {
  calculator = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
      // check if calc mode
      if (false) {
        val[0] = key2asc(keycode);
        if (isdigit(val[0]) || val[0] == '.') {
          if (calcdone) {
            strcat(stack.Y, stack.X);
            memset(stack.X, 0, sizeof(stack.X));
            calcdone = false;
          }
          if (strlen(stack.X) < sizeof(stack.X)) {
            strcat(stack.X, val);
          } else {
            xprintf("%s || %s\n", "TOO BIG BUFFER", stack.X);
          }
        }
        switch (keycode) {
          case KC_ENTER:
            strcpy(stack.Y, stack.X);
            print_stack();
            memset(stack.X, 0, sizeof(stack.X));
            print_stack();
            break;
          case KC_EQUAL:
            print_stack();
            x = atof(stack.X);
            y = atof(stack.Y);
            float u = x+y;
            snprintf(output, 50, "%f", u);
            xprintf("\nresults: %s\n", output);
            strcpy(stack.X, output);
            memset(stack.Y, 0, sizeof(stack.Y));
            print_stack();
            calcdone = true;
            break;
        }
      }
    }
    return true;
};


void matrix_init_user(void) {}
void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {
    if (layer_state & (1L<<1)) {
        PORTB &= ~(1<<5);
    } else {
        PORTB |=  (1<<5);
    }
}
