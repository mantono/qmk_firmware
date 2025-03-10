#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif


/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_TAB, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_LT, KC_RSFT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, MEH(KC_LEFT), MEH(KC_RGHT), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RCTL, CW_TOGG, KC_LALT, LT(3,KC_ESC), LGUI_T(KC_SPC), LT(2,KC_BSPC), KC_ENT, KC_RALT, LGUI(KC_SPC)),
    [1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_EXLM, RALT(KC_2), KC_HASH, KC_QUES, KC_PPLS, KC_PMNS, KC_PSLS, KC_PIPE, KC_RPRN, KC_UNDS, KC_RBRC, KC_TRNS, KC_NUBS, RALT(KC_8), RALT(KC_7), KC_ASTR, KC_AT, KC_NUHS, KC_LPRN, RALT(KC_0), RALT(KC_9), RSFT(KC_NUBS), KC_NUHS, KC_TRNS, KC_RCBR, KC_PLUS, KC_PERC, KC_CIRC, KC_GT, KC_NO, KC_NO, KC_LT, RALT(KC_NUBS), RALT(KC_4), RALT(KC_RBRC), KC_TRNS, KC_INT1, KC_NO, KC_NO, KC_NO, KC_NO, MO(3), KC_NO, KC_NO, KC_NO),
    [2] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_HOME, KC_END, KC_NO, KC_NO, KC_PGDN, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_LEFT, KC_RGHT, KC_TAB, LALT(KC_TAB), KC_DOWN, KC_UP, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MO(3), KC_TRNS, KC_NO, KC_NO, KC_NO),
    [3] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_SCLN, KC_QUOT, KC_LBRC, KC_NO, KC_NO, KC_LBRC, KC_QUOT, KC_SCLN, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO)
};



#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C

