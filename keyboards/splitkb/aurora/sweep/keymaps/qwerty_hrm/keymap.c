#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
    #endif

#include "../../td.c"

// This code comes from https://docs.qmk.fm/features/caps_word#configure-which-keys-are-word-breaking
// but it is modified to work better with tap/dance actions, which would normally cancel
// the caps word, which is not something we want. So instead of the default being to
// return false for key codes not defined here, we will return true by default and only
// return false on certain (explicit) exceptions.
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case TD(TD_E_AE):
        case TD(TD_W_AA):
        case TD(TD_O_OE):
        case RALT(KC_A):
        case RALT(KC_W):
        case RALT(KC_O):
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that deactivates Caps Word
        case KC_SPC:
        case KC_ENT:
        case KC_TAB:
        case KC_COMM:
        case KC_DOT:
        case KC_ESC:
        case KC_BSLS:
        case KC_AT:
        case KC_HASH:
        case KC_DLR:
        case KC_PERC:
        case KC_ASTR:
        case KC_EQL:
        case KC_PLUS:
        case KC_SLSH:
        case KC_LBRC:
        case KC_RBRC:
        case KC_LPRN:
        case KC_RPRN:
        case KC_QUOT:
        case TD(TD_QUOT):
        case KC_DQUO:
        case TD(TD_DQUO):
        case KC_LCBR:
        case KC_RCBR:
        case KC_COLN:
        case KC_SCLN:
        case KC_LT:
        case KC_GT:
        case KC_PIPE:
        case KC_AMPR:
        case KC_CIRC:
        case KC_EXLM:
        case KC_QUES:
        case TD(TD_DOTQU):
        case TD(TD_COMEX):
        case KC_TILD:
        case KC_GRV:
            return false;  // Deactivate Caps Word.

        // By default, all other keycodes will keep continue caps word enabled, but
        // will not be shifted for the given key
        default:
            return true;
    }
}

// Aliases
#define XXXX KC_NO
#define ____ KC_TRNS

enum {
    BASE = 0,
    NAV = 1,
    SYM = 2,
    NUM = 3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q, TD(TD_W_AA), TD(TD_E_AE), KC_R, KC_T,                                     KC_Y, KC_U, KC_I, TD(TD_O_OE), KC_P,
        LT(SYM, KC_A), LGUI_T(KC_S), LALT_T(KC_D), LCTL_T(KC_F), KC_G,      KC_H, RCTL_T(KC_J), LALT_T(KC_K), RGUI_T(KC_L), LT(SYM, KC_ENT),
        KC_Z, KC_X, KC_C, KC_V, KC_B,                                     KC_N, KC_M,  KC_COMM,  KC_DOT, KC_SLSH,
                                         KC_ESC, LT(NAV, KC_SPC),         OSM(MOD_LSFT), KC_TAB
    ),

    [1] = LAYOUT(
        KC_F1,    KC_F2,      KC_F3,      KC_F4,   KC_F5,                                     KC_F6,      KC_F7,      KC_F8,      KC_F9,     KC_F10,
        KC_LGUI,  KC_LSFT,    LALT_T(KC_LEFT),    LCTL_T(KC_RGHT),    KC_DEL,              KC_BSPC,    RCTL_T(KC_DOWN),      LALT_T(KC_UP),   KC_RSFT,  KC_RGUI,
        KC_F11,   KC_F12,     KC_HOME,        KC_END,    XXXX,                                XXXX,       KC_PGUP,       KC_PGDN,       XXXX,       XXXX,
                                                                        ____,    ____,         ____, ____
    ),


// Character frequency from some Rust and Kotlin code
// ⎵: 3660
// ↵: 449
// :: 325
// .: 289
// (: 248
// ): 248
// {: 114
// }: 114
// ;: 107
// =: 92
// ,: 89
// >: 83
// _: 81
// ": 74
// <: 60
// &: 22
// !: 21
// |: 19
// -: 16
// $: 15
// [: 14
// ]: 14
// *: 14
// /: 11
// ?: 7
// #: 7
// ━: 5
// `: 2
// ': 2
// +: 1


   // Tap-dance so '(' on normal press and ')' on hold and '()' on double tap, and the same for '{}', '[]' and '<>'
   // Tap-dance so ' on normal press and '' on double tap with the cursor between both symbols, and same for "
   // Auto-shift digits so we can get the corresponding symbol for each digit
    [2] = LAYOUT(
        //        !              @              #              $              %                                ^              &              *              (              )
                KC_EXLM,       KC_AT,         KC_HASH,       KC_DLR,        KC_PERC,                         KC_CIRC,       KC_AMPR,       KC_ASTR,       KC_LPRN,       KC_RPRN,
        //        `              +              -              =              '                                "              :              _              ?              ;
                KC_GRV,        KC_PLUS,       KC_MINS,       KC_EQL,     TD(TD_QUOT),                     TD(TD_DQUO),      KC_COLN,       KC_UNDS,       KC_QUES,       KC_SCLN,
        //        \              ~              |             ( )            [ ]                              < >            { }            ,                .             /
                KC_BSLS,       KC_TILD,       KC_PIPE,    TD(TD_PAREN),  TD(TD_BRACKET),                  TD(TD_ANGLE),  TD(TD_CURLY),     ____,           ____,         ____,
        //
                                                                    ____,    ____,                ____,       ____
    ),

    [3] = LAYOUT(
         ____,  ____,  ____,  ____,  ____,         ____,  ____,  ____,  ____,  ____,
         KC_1,  KC_2,  KC_3,  KC_4,  KC_5,         KC_6,  KC_7,  KC_8,  KC_9,  KC_0,
         ____,  ____,  ____,  ____,  ____,         ____,  ____,  ____,  ____,  ____,
                              ____,  ____,         ____,   ____
    ),


   // [4] = LAYOUT(
   //     ____,  ____,  KC_DEL,  ____,  ____,                               ____,  ____,  TG(NAV),  ____,  ____,
   //     ____,  ____,  KC_LEFT,  KC_RGHT,  ____,                      KC_BSPC,  KC_DOWN,  KC_UP,  ____,  ____,
   //     ____,  ____,  ____,  ____,  ____,                               ____,  ____,  ____,  ____,  ____,
   //                          ____,  ____,                               ____,  ____
   // ),
// Layer template, copy paste as needed
//    [4] = LAYOUT(
//        XXXX,  XXXX,  XXXX,  XXXX,  XXXX,                               XXXX,  XXXX,  XXXX,  XXXX,  XXXX,
//        XXXX,  XXXX,  XXXX,  XXXX,  XXXX,                               XXXX,  XXXX,  XXXX,  XXXX,  XXXX,
//        XXXX,  XXXX,  XXXX,  XXXX,  XXXX,                               XXXX,  XXXX,  XXXX,  XXXX,  XXXX,
//                             ____,  ____,                               ____,  ____
//    ),

};

// Combos
const uint16_t PROGMEM switcher[] = {LCTL_T(KC_F), RCTL_T(KC_J), COMBO_END};
const uint16_t PROGMEM launcher[] = {KC_G, KC_H, COMBO_END};
const uint16_t PROGMEM num[] = {LT(NAV, KC_SPC), OSM(MOD_LSFT), COMBO_END};
//const uint16_t PROGMEM nav_lock[] = {LT(1, KC_SPC), LSFT_T(KC_BSPC), COMBO_END};
//const uint16_t PROGMEM caps_word[] = {LSFT_T(KC_S), RSFT_T(KC_L), COMBO_END};

combo_t key_combos[] = {
    COMBO(switcher, LGUI(KC_H)),
    COMBO(launcher, LGUI(KC_G)), // keycodes with modifiers are possible too!
    COMBO(num, MO(NUM)),
  //COMBO(nav_lock, TG(1)),
  //  COMBO(caps_word, QK_CAPS_WORD_TOGGLE)
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C


