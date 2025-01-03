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
#include <stdio.h>                 // for snprintf
#include "led.h"
#include "host.h"
#include "dizave.h"                // the dizave library
#include "features/achordion.h"    // https://getreuer.info/posts/keyboards/achordion/index.html

// Layers
enum layer_number {
  _QWERTY = 0,
  _COLEMAK,
  _NAV,
  _NUM, 
  _LEGAL
};



const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t shift_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_TAB);
const key_override_t para_key_override = ko_make_basic(MOD_MASK_SHIFT, DZ_PARA, DZ_SEC);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &delete_key_override,
//    &shift_key_override,
    &para_key_override
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `~  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  _   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BSPC |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   (   |    |    )  |------+------+------+------+------+------|
 * | ESC  |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCtrl| OSM  | NAV  | /Space  /       \Enter \  |RAISE |BackSP| RALT |
 *                   |      | LSFT |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_BSPC,  DZQ_A,  DZQ_S,   DZQ_D,   DZQ_F,   KC_G,                        KC_H,    DZQ_J,   DZQ_K,   DZQ_L,   KC_SCLN, KC_QUOT,
  KC_ESC,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LPRN,  KC_RPRN,     KC_N,    DZ_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_MINS,
                          KC_LCTL,  DZ_LAW,MO(_NAV), KC_SPC,    KC_ENT, MO(_NUM),  KC_DEL,    KC_LALT
),

/* COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `~  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BSPC |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|   [   |    |   ]   |------+------+------+------+------+------|
 * | esc  |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |  -_  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCTL |  OSM | NAV  | /Space  /       \Enter \  | NUM | OSM  | LALT |
 *                   |      | LSFT |      |/       /         \      \ |     | LSFT |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_COLEMAK] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_BSLS,
  KC_BSPC,  KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT,
  KC_ESC,   DZ_Z,   DZ_X,    DZ_C,    DZ_V,    KC_B,  KC_LBRC,  KC_RBRC,  KC_K,    DZ_M,    DZ_COMM, DZ_DOT,  DZ_SLSH,  KC_MINS,
                          KC_LCTL,  DZ_OSS, MO(_NAV),  KC_SPC,   KC_ENT,  MO(_NUM),DZ_OSS,  KC_LALT
),


/* LOWER - NAV
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | boot |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | pscr |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    | pgup | home |  up  | end  |      | del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | gui  | alt  | ctrl | shft |      |-------.    ,-------| pgdn | left | down |right |      | ins  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------| scap |      |      |      |      | caps |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \ law  \ | bspc |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NAV] = LAYOUT(
  QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR,
  _______, DZ_CLSE, XXXXXXX, DZ_VDLT, DZ_VDRT, KC_PSCR,                   KC_PGUP, KC_HOME, KC_UP,   KC_END,  XXXXXXX, KC_DEL,
  _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_SCRL,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX, KC_INS,
  _______, _______, _______, _______, _______, KC_PAUS, KC_LBRC, KC_RBRC, DZ_SCAP,   WLEFT, XXXXXXX,  WRIGHT, XXXXXXX,  KC_CAPS,
                             _______, _______, _______, _______, _______, OSL(_LEGAL), _______, _______
),
/*  NUMBERS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |qwerty|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   [  |  7   |  8   |  9   |  ]   |                    |      |   (  |   )  |     |      |colmak|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |DZ_LAW|   ;  |  4   |  5   |  6   |  =+  |-------.    ,-------|      | RSFT | RCTL | LALT | RGUI |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |  `~  |  1   |  2   |  3   |  -   |-------|    |-------|      |      |      |      |      |DZ_WIN|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |  ,   |   .  |LOWER | /Space  /       \Enter \  |      |      |      |
 *                   |      |      |  0   |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_NUM] = LAYOUT(
  _______, KC_F1,   KC_F2,  KC_F3,   KC_F4, KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  DZ_QWTY,
  _______, KC_LBRC, KC_7,   KC_8,    KC_9,  KC_RBRC,                     XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, DZ_CLMK,
  DZ_LAW,S(KC_SCLN),KC_4,   KC_5,    KC_6,  KC_EQL,                      XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, XXXXXXX,
  _______, KC_GRV,  KC_1,   KC_2,    KC_3,  KC_BSLS, KC_LBRC, KC_RBRC,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DZ_WIN,
                            _______, _______, KC_0,  KC_MINS, _______,  _______, _______, _______
),

/* LEGAL - only useful to NM appellate lawyers who use split ortho keebs. so, just me basically
 * ,-----------------------------------------.                    ,-------------------------------------------.
 * |      |      |      |      |      |      |                    |      |       |       |      |      |DZEMDS|
 * |------+------+------+------+------+------|                    |------+-------+-------+------+------+------|
 * |      |      |  CFR | F.4th| eg   |      |                    | RP   | NMSC  | NMRA  | co   |      |      |
 * |------+------+------+------+------+------|                    |------+-------+-------+------+------+------|
 * |      | ABQ  |  USC | F.3d | See  | P.3d |-------.    ,-------| BIC  | NMCA  | NMSA  | ea   |      |DZRQOT|
 * |------+------+------+------+------+------|       |    |       |------+-------+-------+------+------+------|
 * |      |  NM  |      | F.2d | also | P.2d |-------|    |-------| AB   |  N.M. |       |      |      |      |
 * `-----------------------------------------/       /     \      \-------------------------------------------'
 *                   |      |      |      | / para  /       \      \  |      |      |      |
 *                   |      | nbsp | sec  |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_LEGAL] = LAYOUT(
  XXXXXXX ,_______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, DZ_EMDS,
  _______, XXXXXXX,  DZ_CFR,   DZ_F4, DZ_SEEG, XXXXXXX,                     DZ_RP, DZ_NMSC, DZ_NMRA,   DZ_CO, XXXXXXX, XXXXXXX,
  _______,  DZ_ABQ,  DZ_USC,  DZ_F3D,  DZ_SEE,  DZ_P3D,                    DZ_BIC, DZ_NMCA, DZ_NMSA,   DZ_EA, XXXXXXX, DZ_RQOT,
  _______,  DZ_NM2, XXXXXXX,  DZ_F2D,DZ_SALSO,  DZ_P2D, XXXXXXX, XXXXXXX,   DZ_AB,   DZ_NM, XXXXXXX, XXXXXXX, XXXXXXX, DZ_EMDS,
                             XXXXXXX,  DZ_SEC, DZ_PARA, _______,   DZ_ID,  DZ_ID2, XXXXXXX, XXXXXXX
)

};

//
// achordian functions
//

void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) 
{
  return achordion_opposite_hands(tap_hold_record, other_record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!process_achordion(keycode, record)) { return false; }

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
    if (host_keyboard_led_state().caps_lock) { 
        oled_write_ln("CAPS",true);
    } else {
        oled_write_ln("    ", false);
    } 

      snprintf(layer_state_str, sizeof(layer_state_str), "Lyr%u", layer_state);
      oled_write_ln(layer_state_str, false);

  } else {  // right side
    dizave_render_logo();
  }
    return false;
}
#endif // OLED_ENABLE


