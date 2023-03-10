BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = no 
SWAP_HANDS_ENABLE = no      # Enable one-hand typing

DYNAMIC_TAPPING_TERM_ENABLE = yes

OLED_ENABLE = yes     # OLED display
OLED_DRIVER = SSD1306  # selects the right driver

UNICODE_ENABLE = yes

#CAPS_WORD_ENABLE = yes
#AUTO_SHIFT_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./dizave.c \
        ./lib/keylogger.c \
        ./lib/host_led_state_reader.c \
        ./lib/mode_icon_reader.c 


