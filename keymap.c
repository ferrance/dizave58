/*
Copyright 2022 David Ferrance (@ferrance) 

Derived from the default lily58 keymap, which has no copyright header
and no license or author information.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "led.h"
#include "host.h"
#include <stdio.h> // for snprintf
#include "dizave.h"

// Layers
enum layer_number {
  _QWERTY = 0,
  _COLEMAK,
  _NAV,
  _NUMBERS, 
  _LEGAL
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  _   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BSPC |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   (   |    |    )  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCtrl| tab  | NAV  | /Space  /       \Enter \  |RAISE |BackSP| RALT |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_BSPC,  DZQ_A,  DZQ_S,   DZQ_D,   DZQ_F,   KC_G,                     KC_H,    DZQ_J,   DZQ_K,   DZQ_L,   KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LPRN,  KC_RPRN,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LCTL,  DZ_LAW, MO(_NAV), DZ_SPC, KC_SFTENT, DZ_BSPC, KC_DEL, KC_LALT
),

/* COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BSPC |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|   [   |    |   ]   |------+------+------+------+------+------|
 * | `~   |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |  -_  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCTL |  tab | NAV  | /Space  /       \Enter \  |RAISE | DEL  | LALT |
 *                   |      |      |      |/  lsft /         \      \ |  BSPC|      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_COLEMAK] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_BSLS,
  DZ_OSS,  DZ_A,   DZ_R,    DZ_S,    DZ_T,    KC_D,                     KC_H,    DZ_N,    DZ_E,    DZ_I,    DZ_O,     KC_QUOT,
  KC_GRV,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_MINS,
                        KC_LCTL, DZ_LAW, MO(_NAV), DZ_SPC,   KC_SFTENT,  DZ_BSPC, KC_DEL,  KC_LALT
//                        KC_LCTL, DZ_LAW, MO(_NAV), DZ_SPC,   DZT1,  DZT2, KC_DEL,  KC_LALT
),


/* LOWER - NAV
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | boot |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  1   |  2   |  3   |  4   |  5   |                    |   6  |   7  |   8  |  9   |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | gui  | alt  | ctrl | shft |      |-------.    ,-------| caps | left | down |  up  |right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|  ins |  home| pgdn | pgup | end  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ | bspc |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NAV] = LAYOUT(
  QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                   KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
  _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
                             _______, _______, _______, _______, _______, KC_BSPC, _______, _______
),
/*  NUMBERS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |DZ_LAW|      |      |      |      |      |                    |      |      |      |      |      |qwerty|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   [  |  7   |  8   |  9   |  ]   |                    |      |      |   (  |  )   |      |colmak|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   ;  |  4   |  5   |  6   |  =+  |-------.    ,-------|      | RSFT | RCTL | LALT | RGUI |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |   +  |  1   |  2   |  3   |  -   |-------|    |-------|      |      |   {  |  }   |      |DZ_WIN|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |  ,   |   .  |LOWER | /Space  /       \Enter \  |      |      |      |
 *                   |      |      |  0   |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_NUMBERS] = LAYOUT(
  DZ_LAW , KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  DZ_QWTY,
  DZ_LAW , KC_LBRC, KC_7,    KC_8,    KC_9,  KC_RBRC,                     XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, DZ_CLMK,
  _______, KC_SCLN, KC_4,    KC_5,    KC_6,  KC_EQL,                      XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, XXXXXXX,
  _______, KC_PPLS, KC_1,    KC_2,    KC_3,  KC_MINS, KC_LBRC, KC_RBRC,   XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, DZ_WIN,
                             KC_COMM, KC_DOT, KC_0,  _______, _______,  _______, _______, _______
),

/* LEGAL - only useful to NM appellate lawyers who use split ortho keebs. so, just me basically
 * ,-----------------------------------------.                    ,-------------------------------------------.
 * |      |      |      |      |      |      |                    |      |       |       |      |      |DZEMDS|
 * |------+------+------+------+------+------|                    |------+-------+-------+------+------+------|
 * |      |      |      |DZ_CFR|DZ_USC|      |                    |      |DZ_NMSA|DZ_NMRA|      |      |      |
 * |------+------+------+------+------+------|                    |------+-------+-------+------+------+------|
 * |      |      |      |DZ_SEC|DZ_PAR|      |-------.    ,-------|      | DZ_RP |DZ_BIC | DZ_AB|      |DZRQOT|
 * |------+------+------+------+------+------|       |    |       |------+-------+-------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |       |       |      |      |      |
 * `-----------------------------------------/       /     \      \-------------------------------------------'
 *                   |      |      |      | / nbsp  /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_LEGAL] = LAYOUT(
  XXXXXXX ,_______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, DZ_EMDS,
  _______, XXXXXXX, XXXXXXX,  DZ_CFR,  DZ_USC, XXXXXXX,                   DZ_NMSC, DZ_NMSA, DZ_NMRA, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX,  DZ_SEC, DZ_PARA, XXXXXXX,                   DZ_NMCA, DZ_RP  , DZ_BIC , DZ_AB  , XXXXXXX, DZ_RQOT,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   DZ_NM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             XXXXXXX, XXXXXXX, XXXXXXX, DZ_NBSP, _______, XXXXXXX, XXXXXXX, XXXXXXX
)

};



//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return OLED_ROTATION_270;
}

// When you add source files to SRC in rules.mk, you can use functions.
//const char *read_mode_icon(bool swap);

bool oled_task_user(void) {
  if (is_keyboard_master()) {


    oled_write_ln("Layer", false);

    char layer_state_str[24];
    if (layer_state==2) {
      oled_write_ln("clmak", false);
    } else if ( layer_state == 0 ) {
      oled_write_ln( (default_layer_state==2) ? "CLMAK" : "QWRTY", false );
    } else if (layer_state == 4 ) {
      oled_write_ln("-nav-", false);
    } else if (layer_state == 8 ) {
      oled_write_ln("-num-", false);
    } else if (layer_state == 16) {
      oled_write_ln("-law-", false);
    } else {
      snprintf(layer_state_str, sizeof(layer_state_str), "Lyr%u", layer_state);
      oled_write_ln(layer_state_str, false);
    }
    
    oled_write_ln("",false);

    dizave_render_master();


    // display apple / windows logo
    dizave_render_bootmagic_status(!is_mac());
    oled_write_ln("    ", false);

    dizave_render_numbers(layer_state==8);
    oled_write_ln("     ", false);

    // CAPS LOCK
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) { 
        oled_write_ln("CAPS",true);
    } else {
        oled_write_ln("    ", false);
    } 


  } else {  // right side
    dizave_render_logo();
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch(keycode) {
    case DZ_QWTY:
       set_single_persistent_default_layer(_QWERTY);
      break;
    case DZ_CLMK:
      set_single_persistent_default_layer(_COLEMAK);
      break;
    default:
	return dizave_process_record_user(keycode, record);
      break;
  }

  return true;
}
