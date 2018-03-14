#include "rasmus.h"
#include "quantum.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_SHRG:
      if (!record->event.pressed) {
        SEND_STRING(TYPE_SHRUG);
      }
      return false;
      break;
  }
  return process_record_keymap(keycode, record);
}
