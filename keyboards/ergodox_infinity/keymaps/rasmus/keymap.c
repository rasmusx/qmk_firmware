#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "ergodox_infinity.h"
#include "calc.h"

#define BASE 0 // default layer
#define FL1 1 // symbols
#define GAME 2 // media keys
#define ESDF 3 // media keys
#define CALCU 4 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  CALC,
  C_0,
  C_1,
  C_2,
  C_3,
  C_4,
  C_5,
  C_6,
  C_7,
  C_8,
  C_9,
};

enum macro_id {
  SHRUG,
};

#define TYPE_SHRUG MACRO( \
  D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), \
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
  T(SPACE), END \
)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |  `   |           |   -  |   6  |   7  |   8  |   9  |   0  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  [   |           |   ]  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Fn1    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  \   |           |Shrug |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl | Home | End  | LAlt | LGui |                                       | RGui | RAlt |  Del |  Ins | Ctrl |
 *   `----------------------------------'                                       `----------------------------------'
 *
 *                                        ,-------------.       ,-------------.
 *                                        | Ins  | PtSc |       | Calc  | Esc |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Del  |       | PgUp |        |      |
 *                                 | Space| Bsp  |------|       |------| Fn1    |Enter |
 *                                 |      |      | Esc  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_GRV,
        KC_TAB ,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,
        MO(FL1),KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_BSLS,
        KC_LCTL,KC_HOME,KC_END ,KC_LALT,KC_LGUI,
                                        KC_INS, TG(GAME),
                                                        KC_DEL,
                                        KC_SPC, KC_BSPC,KC_ESC,

        // right hand
             KC_MINS,KC_6,   KC_7,   KC_8,   KC_9   ,KC_0  , KC_EQL,
             KC_RBRC,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSLS,
                     KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
             M(SHRUG),KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
                             KC_RGUI,KC_RALT,KC_DEL ,KC_INS ,KC_RCTL,
             TG(CALCU),        KC_LOCK,
             KC_PGUP,
             KC_PGDN,MO(FL1),KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * | Esc     |  F1  |  F2  |  F3  |  F4  |  F5  |      |           | F11  |  F6  |  F7  | F8   | F9   | F10  | F12    |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | Version |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Caps    |      |      |      |      |      |------|           |------| Le   | Do   | Up   | Ri   |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      | PgUp |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      | Home | PgDn | End  |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[FL1] = LAYOUT_ergodox(
       // left hand
       KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_CAPS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          EPRM,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,RESET,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_F10 , KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F12,
       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_LEFT, KC_DOWN,KC_UP  , KC_RIGHT,KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS,
                         KC_TRNS,KC_TRNS, KC_HOME, KC_PGDN, KC_END,
       RESET,   KC_TRNS,
       KC_TRNS,
       TG(CALCU), KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      | Prev | Play | Next |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CapsLk |      |MsLeft|MsDown|MsRght|      |------|           |------|      | VolD | Mute | VolU |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Stop |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |EEPROM| Menu |      | Lclk | Rclk |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | Reset|      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
//[FL2] = LAYOUT_ergodox(
//       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
//       KC_CAPS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
//       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//       EPRM,    KC_APP,  KC_TRNS, KC_BTN1, KC_BTN2,
//                                           KC_TRNS, KC_TRNS,
//                                                    KC_TRNS,
//                                  KC_TRNS, KC_TRNS, KC_TRNS,
//    // right hand
//       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//       KC_TRNS,  KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS,
//                 KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_TRNS,
//       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MSTP, KC_TRNS, KC_TRNS, KC_TRNS,
//                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//       RESET,   KC_TRNS,
//       KC_TRNS,
//       KC_TRNS, KC_TRNS, KC_TRNS
//),
// MEDIA AND MOUSE
[GAME] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       TG(ESDF),  KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[ESDF] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_TRNS,
       KC_TRNS, KC_G,    KC_A,    KC_S,    KC_D,    KC_F,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                 KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[CALCU] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       //KC_TRNS,  KC_TRNS, KC_P7  , KC_P8  , KC_P9  , KC_PSLS, KC_TRNS,
       //KC_TRNS,  KC_TRNS, KC_P4  , KC_P5  , KC_P6  , KC_PAST, KC_TRNS,
       //          KC_TRNS, KC_P1  , KC_P2  , KC_P3  , KC_PMNS, KC_TRNS,
       //KC_TRNS,  KC_TRNS, KC_P0  , KC_PDOT, KC_PENT, KC_PPLS, KC_TRNS,
       //                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       //KC_TRNS,  KC_TRNS,
       //KC_TRNS,
       //KC_TRNS, KC_TRNS, KC_TRNS
       KC_TRNS,  KC_TRNS, C_7  , C_8  , C_9  , KC_PSLS, KC_TRNS,
       KC_TRNS,  KC_TRNS, C_4  , C_5  , C_6  , KC_PAST, KC_TRNS,
                 KC_TRNS, C_1  , C_2  , C_3  , KC_PMNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, C_0  , KC_TRNS, KC_TRNS, KC_PPLS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(FL1)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case SHRUG:
        return (record->event.pressed ? TYPE_SHRUG : MACRO_NONE );
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
    case CALC:
    //  layer_on(CALCU);
      //calc_on();
    case C_0:
      if (record->event.pressed) {
        calc_add('0');
      }
      return false;
      break;
    case C_1:
      if (record->event.pressed) {
        calc_add('1');
      }
      return false;
      break;
    case C_2:
      if (record->event.pressed) {
        calc_add('2');
      }
      return false;
      break;
    case C_3:
      if (record->event.pressed) {
        calc_add('3');
      }
      return false;
      break;
    case C_4:
      if (record->event.pressed) {
        calc_add('4');
      }
      return false;
      break;
    case C_5:
      if (record->event.pressed) {
        calc_add('5');
      }
      return false;
      break;
    case C_6:
      if (record->event.pressed) {
        calc_add('6');
      }
      return false;
      break;
    case C_7:
      if (record->event.pressed) {
        calc_add('7');
      ergodox_right_led_1_on();
      }
      return false;
      break;
    case C_8:
      if (record->event.pressed) {
        calc_add('8');
      ergodox_right_led_2_on();
      }
      return false;
      break;
    case C_9:
      if (record->event.pressed) {
        calc_add('9');
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case GAME:
            ergodox_right_led_2_on();
            break;
        //case CALCU:
        //    ergodox_right_led_3_on();
        //    break;
        default:
            // none
            break;
    }

};

