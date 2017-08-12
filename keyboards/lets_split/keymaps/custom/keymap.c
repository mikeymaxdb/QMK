#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _LOWER 2
#define _RAISE 3
#define _NAV 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  NAV,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define SUP_1 ACTION_MODS_KEY(MOD_LGUI, KC_1)
#define SUP_2 ACTION_MODS_KEY(MOD_LGUI, KC_2)
#define SUP_3 ACTION_MODS_KEY(MOD_LGUI, KC_3)
#define SUP_4 ACTION_MODS_KEY(MOD_LGUI, KC_4)
#define SUP_5 ACTION_MODS_KEY(MOD_LGUI, KC_5)
#define SUP_6 ACTION_MODS_KEY(MOD_LGUI, KC_6)
#define SUP_7 ACTION_MODS_KEY(MOD_LGUI, KC_7)

#define CTESC ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |ADJUST|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | GUI  | ALT  | NAV  |Lower |Enter |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  MT(MOD_LCTL, KC_ESC),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ADJUST , \
  KC_LCTL, KC_LGUI, KC_LALT, NAV,     LOWER,   KC_ENT,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |ADJUST|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | GUI  | ALT  | NAV  |Lower |Enter |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = KEYMAP( \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ADJUST , \
  KC_LCTL, KC_LGUI, KC_LALT, NAV,     LOWER,   KC_ENT,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |      |      |      |      |      |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |   #  |   $  |   ^  |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   &  |   *  |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, _______, _______, _______, _______, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_DEL,  KC_DLR,  KC_PERC, KC_CIRC, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_AMPR, KC_ASTR, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |      |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |   3  |   4  |   5  |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   7  |   8  |   9  |   0  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_GRV,  KC_1,    KC_2,    KC_3,_______, _______, _______, _______,_______, _______, _______,    KC_BSPC, \
  KC_DEL,  KC_4,   KC_5,   KC_6, _______,   _______,   _______,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_7,   KC_8,   KC_9, KC_0,  _______,  _______,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Navigation */
[_NAV] =  KEYMAP( \
  _______, SUP_1,   SUP_2,   SUP_3,   SUP_4,   SUP_5,   SUP_6,   SUP_7, _______, _______, _______, _______, \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * |      |QWERTY|COLMAK|      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Reset|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | PLAY | VOLD | VOLU | NEXT |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  _______, QWERTY,COLEMAK, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
  RESET, _______, _______, _______, _______, _______, _______, _______,  _______, _______,  _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD, KC_VOLU, KC_MNXT \
)


};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case NAV:
      if (record->event.pressed) {
        layer_on(_NAV);
      } else {
        layer_off(_NAV);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}