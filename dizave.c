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
#include "dizave.h"


// is_mac() - returns true if keeb is configure for mac use
//
// if ctl and gui are swapped, mac, else windows
// magic is already storing this in the EEPROM
//
bool is_mac(void) {
  return keymap_config.swap_lctl_lgui;
}

// sets up the keeb to talk to windows
//   unicode mode => wincompose
//   don't swap ctl and gui (dizave keebs default to GACS home row mods
//
void dizave_set_win_mode(void) {

  // toggle ctrl and gui
  keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = false;
        
  // toggle unicode mode
  set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);

}

void dizave_set_mac_mode(void) {
  keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = true;
  set_unicode_input_mode(UNICODE_MODE_MACOS);
}


void dizave_render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}


// renders the master OLED
//  - expects that layer has already been written
//  - expects a vertical OLED
//
void dizave_render_master(void) {

    // show status of home row mods
    if (is_mac()) {   // MAC

      oled_write("C", get_mods() & MOD_MASK_CTRL);
      oled_write("A", get_mods() & MOD_MASK_ALT);
      oled_write("G", get_mods() & MOD_MASK_GUI);
      oled_write_ln("S", get_mods() & MOD_MASK_SHIFT);
//      oled_write_ln("mac",false);

   } else {  // WIN

      oled_write("G", get_mods() & MOD_MASK_GUI);
      oled_write("A", get_mods() & MOD_MASK_ALT);
      oled_write("C", get_mods() & MOD_MASK_CTRL);
      oled_write_ln("S", get_mods() & MOD_MASK_SHIFT);
      //oled_write_ln("pc",false);
   }

}

void dizave_render_numbers(bool show) 
{
  if (show) {
      if (get_mods() & MOD_MASK_SHIFT) {
        oled_write("{&*(}",false);
        oled_write(":$%^+",false);
        oled_write("+!@#-",false);
      } else {
        oled_write("[789]",false);
        oled_write(";456=",false);
        oled_write("+123-",false); 
      }
  } else {
    oled_write_ln("",false);
    oled_write_ln("",false);
    oled_write_ln("",false);
  }
}

void dizave_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool dizave_process_record_user(uint16_t keycode, keyrecord_t *record) 
{
  switch(keycode) {

    case DZ_WIN:
      if (record->event.pressed) {
        if (is_mac()) {
            dizave_set_win_mode();
        } else {
            dizave_set_mac_mode();
        }
        // save mode into eeprom
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;

    case DZ_CLSE:
      if (record->event.pressed) {
        if (is_mac()) {
          SEND_STRING(SS_LGUI("q"));
        } else {
          SEND_STRING(SS_LALT(SS_TAP(X_F4)));
        }
      }
      return false;

    // mac - command shift 4
    // win - gui shift S
    case DZ_SCAP:
      if (is_mac()) {
        SEND_STRING(SS_LGUI("$"));
      } else {
        SEND_STRING(SS_LGUI("S"));
      }
      return false;

    case DZ_NMSA:
      if (record->event.pressed) {
        SEND_STRING("NMSA 1978, ");
      }
      return false;

    case DZ_NMRA:
      if (record->event.pressed) {
        SEND_STRING("Rule NMRA "SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
      }
      return false;

    case DZ_USC:
      if (record->event.pressed) {
        SEND_STRING("U.S.C. ");
        send_unicode_string("§");
      }
      return false;

    case DZ_CFR:
      if (record->event.pressed) {
        SEND_STRING("C.F.R. ");
        send_unicode_string("§");
      }
      return false;

    case DZ_RP:
      if (record->event.pressed) {
        if (is_mac()) {
          SEND_STRING(SS_LGUI("B")"[RP ]"SS_LGUI("B")" "SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        } else {
          SEND_STRING(SS_LCTL("B")"[RP ]"SS_LCTL("B")" "SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
      }
      return false;

    case DZ_BIC:
      if (record->event.pressed) {
        if (is_mac()) {
          SEND_STRING(SS_LGUI("B")"[BIC ]"SS_LGUI("B")" "SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        } else {
          SEND_STRING(SS_LCTL("B")"[BIC ]"SS_LCTL("B")" "SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
       
      }
      return false;

    case DZ_AB:
      if (record->event.pressed) {
        if (is_mac()) {
          SEND_STRING(SS_LGUI("B")"[AB ]"SS_LGUI("B")" "SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        } else {
          SEND_STRING(SS_LCTL("B")"[AB ]"SS_LCTL("B")" "SS_TAP(X_LEFT)SS_TAP(X_LEFT));
        }
      }
      return false;

    case DZ_NM:
      if (record->event.pressed) {
        SEND_STRING("N.M.");
      }
      return false;

    case DZ_NMSC:
      if (record->event.pressed) {
        SEND_STRING("-NMSC-");
      }
      return false;

    case DZ_NMCA:
      if (record->event.pressed) {
        SEND_STRING("-NMCA-");
      }
      return false;

    case DZ_F4:
      if (record->event.pressed) {
        SEND_STRING("F.4th");
      }
      return false;

    case DZ_F3D:
      if (record->event.pressed) {
        SEND_STRING("F.3d");
      }
      return false;

    case DZ_F2D:
      if (record->event.pressed) {
        SEND_STRING("F.2d");
      }
      return false;

    case DZ_P3D:
      if (record->event.pressed) {
        SEND_STRING("P.3d");
      }
      return false;

    case DZ_P2D:
      if (record->event.pressed) {
        SEND_STRING("P.2d");
      }
      return false;

    case DZ_ABQ:
      if (record->event.pressed) {
         SEND_STRING("Albuquerque");
      }
      return false;
      
    case DZ_NM2:
      if (record->event.pressed) {
         SEND_STRING("New Mexico");
      }
      return false;

    case DZ_SEE:
      if (record->event.pressed) {
        if (is_mac()) {
          SEND_STRING(SS_LGUI("i")"See"SS_LGUI("i")" ");
        } else {
          SEND_STRING(SS_LCTL("i")"See"SS_LCTL("i")" ");
        }
      }
      return false;

    case DZ_SEEG:
      if (record->event.pressed) {
        if (is_mac()) {
          SEND_STRING(SS_LGUI("i")"See, e.g."SS_LGUI("i")", ");
        } else {
          SEND_STRING(SS_LCTL("i")"See, e.g."SS_LCTL("i")", ");
        }
      }
      return false;

    case DZ_SALSO:
      if (record->event.pressed) {
        if (is_mac()) {
          SEND_STRING(SS_LGUI("i")"See also"SS_LGUI("i")" ");
        } else {
          SEND_STRING(SS_LCTL("i")"See also"SS_LCTL("i")" ");
        }
      }
      return false;

    case DZ_ID:
      if (record->event.pressed) {
        if (is_mac()) {
          SEND_STRING(SS_LGUI("i")"Id."SS_LGUI("i")" ");
        } else {
          SEND_STRING(SS_LCTL("i")"Id."SS_LCTL("i")" ");
        }
      }
      return false;


    case DZ_ID2:
      if (record->event.pressed) {
        if (is_mac()) {
          SEND_STRING(SS_LGUI("i")"id."SS_LGUI("i")" ");
        } else {
          SEND_STRING(SS_LCTL("i")"id."SS_LCTL("i")" ");
        }
      }
      return false;

      case DZ_EA:
      if (record->event.pressed) {
        SEND_STRING("(emphasis added)");
      }
      return false;      

      case DZ_CO:
      if (record->event.pressed) {
        SEND_STRING("(citations omitted)");
      }
      return false;      

      case DZ_ROG:
      if (record->event.pressed) {
        SEND_STRING("Interrogatory");
      }
      return false;      

    }  // switch

  return true;

}