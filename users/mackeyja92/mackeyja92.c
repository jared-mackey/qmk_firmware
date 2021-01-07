#include QMK_KEYBOARD_H
#include "mackeyja92.h"

void tmux_prefix(void) {
  register_code(KC_LCTL);
  tap_code(KC_A);
  unregister_code(KC_LCTL);
}

void dance_tmux_scroll_mac_lock(qk_tap_dance_state_t *state, void *user_data) {
  // tap dances between sending the tmux scroll command and locking the mac
  // Single tap goes into tmux scroll
  // Double tap or more locks the mac
  if (state->count == 1) {
    // Only pressed once, send TMUX scroll command
    tmux_prefix();
    tap_code(KC_LBRC);
  } else {
    // Double tapped, send lock command
    // Send the default key binding to lock a Mac laptop
    register_code(KC_LGUI);
    register_code(KC_LCTRL);
    tap_code(KC_Q);
    unregister_code(KC_LCTRL);
    unregister_code(KC_LGUI);
  }
  // Reset tap dance state back to original since we don't store any long term state or hold keys for any duration
  reset_tap_dance(state);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
