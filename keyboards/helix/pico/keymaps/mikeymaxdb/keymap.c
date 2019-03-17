#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

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
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _SYMB,
    _NUMB,
    _NAV,
    _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

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

    [_QWERTY] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTLESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ADJUST,
        KC_LCTL, KC_LGUI, KC_LALT, NAV,     SYMB,    KC_ENT,  KC_NO, KC_NO, KC_SPC,  NUMB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_COLEMAK] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                  KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
        CTLESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                  KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ADJUST,
        KC_LCTL, KC_LGUI, KC_LALT, NAV,     SYMB,    KC_ENT,  KC_NO, KC_NO, KC_SPC,  NUMB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_SYMB] = LAYOUT(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, _______, _______,                  _______, _______, _______, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_DEL,  KC_DLR,  KC_PERC, KC_CIRC, _______, _______,                  _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        _______, KC_AMPR, KC_ASTR, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NUMB] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    _______, _______,                   _______, _______, _______, _______, _______, KC_BSPC,
        KC_DEL,  KC_4,    KC_5,    KC_6,    _______, _______,                   _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, KC_7,    KC_8,    KC_9,    KC_0,    _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT(
        _______, SUP_1,   SUP_2,   SUP_3,   SUP_4,   _______,                   KC_DOWN, KC_RGHT, _______,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   KC_LEFT, _______, _______, _______, _______,   _______,
        _______, _______, _______, _______, _______, _______,                   KC_UP,   _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
        _______, QWERTY,  COLEMAK, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        RESET,   _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD, KC_VOLU, KC_MNXT
    ),

};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

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
  }
  return true;
}

void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_SYMB (1<<_SYMB)
#define L_NUMB (1<<_NUMB)
#define L_NAV (1<<_NAV)
#define L_ADJUST (1<<_ADJUST)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Keeb"));
           break;
        case L_SYMB:
           matrix_write_P(matrix, PSTR("Symbols"));
           break;
        case L_NUMB:
           matrix_write_P(matrix, PSTR("Numbers"));
           break;
        case L_NAV:
           matrix_write_P(matrix, PSTR("Navigation"));
           break;
        case L_ADJUST:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
