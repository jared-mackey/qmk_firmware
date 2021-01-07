#pragma once

#define _NORMAN 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  NORMAN = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};


#define KC_ KC_TRNS
#define _______ KC_TRNS
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_CTRLN LCTL_T(KC_N)
#define KC_CTRLT RCTL_T(KC_T)
#define KC_LSPC LT(_LOWER, KC_SPC)
#define KC_RBSPC LT(_RAISE, KC_BSPC)

void dance_tmux_scroll_mac_lock(qk_tap_dance_state_t *state, void *user_data);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
void tmux_prefix(void);
