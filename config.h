/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

/* Select hand configuration */
#define MASTER_LEFT

// sexy dizave logo
#undef OLED_FONT_H
#define OLED_FONT_H "dizave58.c"

// home row mods
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200

#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS, UNICODE_MODE_WINCOMPOSE

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// trying to be small
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT