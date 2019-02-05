/* Copyright 2015-2017 Jack Humbert
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

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum planck_layers {
    _QWERTY,
    _COLEMAK,
    _SYMB,
    _NUMB,
    _NAV,
    _ADJUST
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
};
#define SUP_1 LGUI(KC_1)
#define SUP_2 LGUI(KC_2)
#define SUP_3 LGUI(KC_3)
#define SUP_4 LGUI(KC_4)

#define CTLESC CTL_T(KC_ESC)

#define SYMB   MO(_SYMB)
#define NUMB   MO(_NUMB)
#define NAV    MO(_NAV)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_planck_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTLESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ADJUST,
        KC_LCTL, KC_LGUI, KC_LALT, NAV,     SYMB,    KC_ENT,  KC_SPC,  NUMB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_COLEMAK] = LAYOUT_planck_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        CTLESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ADJUST,
        KC_LCTL, KC_LGUI, KC_LALT, NAV,     SYMB,    KC_ENT,  KC_SPC,  NUMB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_SYMB] = LAYOUT_planck_grid(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_DEL,  KC_DLR,  KC_PERC, KC_CIRC, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_AMPR, KC_ASTR, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NUMB] = LAYOUT_planck_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    _______, _______, _______, _______, _______, _______, _______, KC_BSPC,
        KC_DEL,  KC_4,    KC_5,    KC_6,    _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT_planck_grid(
        _______, SUP_1,   SUP_2,   SUP_3,   SUP_4,   _______, _______, _______, _______, _______, _______, _______,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_planck_grid(
        _______, QWERTY,  COLEMAK, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD, KC_VOLU, KC_MNXT
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
    }
    return true;
}

