#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _SYMB 2
#define _NUMB 3
#define _NAV 4
#define _ADJUST 5

#define SUP_1 LGUI(KC_1)
#define SUP_2 LGUI(KC_2)
#define SUP_3 LGUI(KC_3)
#define SUP_4 LGUI(KC_4)

#define CTLESC CTL_T(KC_ESC)
#define ALTTAB LALT_T(KC_TAB)
#define EXPLOD LGUI(KC_UP)

#define SYMB   MO(_SYMB)
#define NUMB   MO(_NUMB)
#define NAV    MO(_NAV)
#define ADJUST MO(_ADJUST)

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    RGBRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
            ALTTAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            CTLESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ADJUST,
            NAV,     SYMB,    KC_ENT,  KC_SPC,  NUMB,    KC_LGUI
            ),

    [_COLEMAK] = LAYOUT(
            ALTTAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
            CTLESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ADJUST,
            NAV,     SYMB,    KC_ENT,  KC_SPC,  NUMB,    KC_LGUI
            ),

    [_SYMB] = LAYOUT(
            KC_TILD, KC_EXLM, KC_AT,   KC_HASH, _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, KC_BSPC,
            KC_DEL,  KC_DLR,  KC_PERC, KC_CIRC, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
            _______, KC_AMPR, KC_ASTR, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______
            ),

    [_NUMB] = LAYOUT(
            KC_GRV,  KC_1,    KC_2,    KC_3,    _______, _______, _______, _______, _______, _______, _______, KC_BSPC,
            KC_DEL,  KC_4,    KC_5,    KC_6,    _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
            _______, KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______
            ),
    [_NAV] = LAYOUT(
            _______, SUP_1,   SUP_2,   SUP_3,   SUP_4,   _______, KC_DOWN, KC_RGHT, _______, EXPLOD, _______, _______,
            _______, _______, _______, _______, _______, _______, KC_LEFT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
            _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______
            ),
    [_ADJUST] = LAYOUT(
            _______, QWERTY,  COLEMAK, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            RESET,   _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD, KC_VOLU, KC_MNXT, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______
            ),
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
    #endif
    iota_gfx_init(!has_usb());   // turns on the display
}

const char *read_logo(void);

void matrix_scan_user(void) {
    iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        matrix_write(matrix, read_logo());
    } else {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL<<_QWERTY);
            }
            return false;
        case COLEMAK:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL<<_COLEMAK);
            }
            return false;
        case RGB_MOD:
            if (record->event.pressed) {
    #ifdef RGBLIGHT_ENABLE
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_config.mode;
    #endif
            }
            return false;
        case RGBRST:
            if (record->event.pressed) {
    #ifdef RGBLIGHT_ENABLE
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
    #endif
            }
            break;
    }
    return true;
}
