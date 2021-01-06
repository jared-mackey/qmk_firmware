#include QMK_KEYBOARD_H
#include "mackeyja92.h"

void tmux_prefix(void) {
  register_code(KC_LCTL);
  tap_code(KC_A);
  unregister_code(KC_LCTL);
}

bool handle_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TMUX_SCROLL:
      SEND_STRING("TEST");
      clear_keyboard();
      // Send TMUX escape and then `[` to go into scroll mode
      tmux_prefix();
      tap_code(KC_LBRC);
      return true;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
  }
  return true;
}
