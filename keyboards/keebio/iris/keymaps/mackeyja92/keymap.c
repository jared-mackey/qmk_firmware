#include QMK_KEYBOARD_H
#include "mackeyja92.h"

#define KC_RGB_TOG RGB_TOG
#define KC_LOCK TD(TDLOCK)

enum {
  TDLOCK = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once to enter tmux, tap twice to lock the mac
  [TDLOCK] = ACTION_TAP_DANCE_FN(dance_tmux_scroll_mac_lock)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NORMAN] = LAYOUT_kc(
  //,----+----+----+----+----+----.                 ,----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  ,                   6  , 7  , 8  , 9  , 0  ,CAPS,
  //|----+----+----+----+----+----|                 |----+----+----+----+----+----|
     TAB , Q  , W  , D  , F  , K  ,                   J  , U  , R  , L  ,SCLN,MINS ,
  //|----+----+----+----+----+----|                 |----+----+----+----+----+----|
     ESC,  A  , S  , E  ,CTRLT,G  ,                   Y  ,CTRLN,I  , O  , H  ,QUOT,
  //|----+----+----+----+----+----+----.        ,----|----+----+----+----+----+----|
     LSPO, Z  , X  , C  , V  , B , LOCK,        LALT, P  , M  ,COMM,DOT ,SLSH,RSPC,
  //`----+----+----+--+-+----+----+----/        \----+----+----+----+----+----+----'
                       RASE,LGUI,BSPC,            ENT ,SPC, LOWR
  //                  `----+----+----'           `+---+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     GRV ,    ,    ,    ,    ,    ,                   ,AMPR,ASTR,LPRN,RPRN,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,MINS,EQL ,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,MPLY,         ,    ,UNDS,PLUS,LCBR,RCBR,PIPE,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                            ,    ,BSPC,        ENT, SPC,
  //                  `----+----+----'        `----+----+----'
  ),
   [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 , F10, F11,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,LEFT,DOWN, UP ,RGHT,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,     ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,     ,            ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

 [_ADJUST] = LAYOUT(
  //,------+--------+--------+--------+--------+--------.                    ,------+--------+--------+--------+--------+--------.
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+--------+--------+--------+--------+--------|                    |------+--------+--------+--------+--------+--------|
    XXXXXXX, RGB_HUD, RGB_SAD, RGB_SAI, RGB_HUI, XXXXXXX,                    XXXXXXX, XXXXXXX, RESET  , XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+--------+--------+--------+--------+--------|                    |------+--------+--------+--------+--------+--------|
    XXXXXXX, RGB_VAI, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+--------+--------+--------+--------+--------+--------. ,-------|--------+--------+--------+--------+--------+--------|
    XXXXXXX, RGB_M_X, RGB_M_G, RGB_M_P, XXXXXXX, XXXXXXX, RGB_TOG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //`------+--------+--------+--------+--------+---+----+-------/      \------------+--------+----+---+--------+--------+--------'
                                      XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX
  //                                  `-------+--------+-------'        `-------+--------+--------'
  ),

};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  rgblight_increase_hue();
  return process_record_user(keycode, record);
}

void encoder_update_user(uint8_t index, bool clockwise) {
  // On the raise layer use the wheel to control RGB brightness
  if (IS_LAYER_ON(_ADJUST)) {
    if (clockwise) {
      // Do not turn up the brigtness if it is already at max
      if(rgblight_get_val() < 255) {
        // Turn up the brightness
        rgblight_increase_val();
      }
    } else {
      // Do not turn down the brightness if it is already at 0
      if(rgblight_get_val() > 0) {
        // Turn down the brightness
        rgblight_decrease_val();
      }
    }

    return;
  }

  // On the lower layer use the wheel to control music tracks
  if (IS_LAYER_ON(_LOWER)) {
    if (clockwise) {
      tap_code(KC_MNXT);
    } else {
      tap_code(KC_MPRV);
    }
    return;
  }

  // On the normal layer use the wheel to page up and down
  if (clockwise) {
    tap_code(KC_PGDN);
  } else {
    tap_code(KC_PGUP);
  }
}
