EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.

# If you want to change the display of OLED, you need to change here
SRC +=  ./keymaps/mikeymaxdb/glcdfont.c \
        ./lib/rgb_state_reader.c \
        ./lib/logo_reader.c \
