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

#include "planck.h"
#include "action_layer.h"
#include "mousekey.h"
#include "config.h"
#include <util/delay.h>

enum planck_layers {
  _DVORAK = 0,
  _NUM_SYM,
  _MOUSE,
  _ADJUST,
  _WOW,
  _QWERTY
};

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  NUM_SYM,
  MOUSE,
  WOW,
  QWERTY,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {ALT_T(KC_TAB),  KC_QUOT,  KC_COMM, KC_DOT,  KC_P,   KC_Y,    KC_F,          KC_G,     KC_C,     KC_R,    KC_L,    MT(MOD_RALT, KC_BSPC)},
  {GUI_T(KC_EQL),  KC_A,     KC_O,    KC_E,    KC_U,   KC_I,    KC_D,          KC_H,     KC_T,     KC_N,    KC_S,    MT(MOD_RGUI, KC_MINS)},
  {SFT_T(KC_SLSH), KC_SCLN,  KC_Q,    KC_J,    KC_K,   KC_X,    KC_B,          KC_M,     KC_W,     KC_V,    KC_Z,    MT(MOD_RSFT, KC_ENTER)},
  {XXXXXXX,        XXXXXXX,  XXXXXXX, XXXXXXX, MOUSE,  KC_SPC,  CTL_T(KC_ESC), NUM_SYM,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX}
},

[_NUM_SYM] = {
  {ALT_T(KC_TAB),   KC_DOT,  KC_7,    KC_8,    KC_9,   KC_ASTR, KC_HASH,       KC_EXLM,  KC_PLUS, KC_PIPE, KC_DLR,  MT(MOD_RALT, KC_BSPC)},
  {GUI_T(KC_EQL),   KC_0,    KC_4,    KC_5,    KC_6,   KC_AT,   KC_TILD,       KC_CIRC,  KC_LPRN, KC_RPRN, KC_PERC, MT(MOD_RGUI, KC_MINS)},
  {CTL_T(KC_BSLS),  KC_COLN, KC_1,    KC_2,    KC_3,   KC_AMPR, KC_GRV,        KC_LCBR,  KC_RCBR, KC_LBRC, KC_RBRC, MT(MOD_RCTL, KC_ENTER)},
  {XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, MOUSE,  KC_SPC,  CTL_T(KC_ESC), NUM_SYM,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
},

[_MOUSE] = {
  {ALT_T(KC_TAB),  XXXXXXX, KC_PGUP, KC_UP,   KC_PGDN, XXXXXXX, XXXXXXX,       KC_WH_U, KC_MS_U, KC_WH_D, KC_BTN3, MT(MOD_RALT, KC_BSPC)},
  {GUI_T(KC_EQL),  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,       KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN2, MT(MOD_RGUI, KC_MINS)},
  {CTL_T(KC_BSLS), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN4, MT(MOD_RCTL, KC_ENTER)},
  {XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, MOUSE,   KC_SPC,  KC_BTN1, NUM_SYM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |WOW   |QWERTY|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL },
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, WOW,     QWERTY}
},

/* WoW
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_WOW] = {
  {KC_TAB,  KC_TAB,  KC_COMM, KC_UP,   KC_P,        KC_Y,   KC_F,       KC_G,       KC_C,    KC_R,   KC_L,    KC_BSPC},
  {KC_ESC,  KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT,     KC_I,   KC_D,       KC_H,       KC_T,    KC_N,   KC_S,    KC_MINS},
  {KC_LGUI, KC_LSFT, KC_Q,    KC_J,    KC_K,        KC_X,   KC_B,       KC_M,       KC_W,    KC_V,   KC_Z,    KC_A},
  {DVORAK, XXXXXXX, XXXXXXX, XXXXXXX, MO(_MOUSE),  KC_SPC, KC_MS_BTN1, KC_MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
},


/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {DVORAK,  KC_LCTL, KC_LALT, KC_LGUI, MOUSE,   KC_SPC,  KC_SPC,  NUM_SYM, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
}

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case WOW:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_WOW);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case NUM_SYM:
      if (record->event.pressed) {
        layer_on(_NUM_SYM);
        update_tri_layer(_NUM_SYM, _MOUSE, _ADJUST);
      } else {
        layer_off(_NUM_SYM);
        update_tri_layer(_NUM_SYM, _MOUSE, _ADJUST);
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
        update_tri_layer(_NUM_SYM, _MOUSE, _ADJUST);
      } else {
        layer_off(_MOUSE);
        update_tri_layer(_NUM_SYM, _MOUSE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
