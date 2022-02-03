// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=128 sts=4 ts=24 sw=4 et ai:
#include QMK_KEYBOARD_H
#include "wait.h"

// This is a programmable keyboard with 10 layers:
// * 2 choices for the default layer (_BL1, _BL2)
// * 5 temporary top layers (_FL1, _FL2, _FL3, _FL4, _FL5)
//     * (_FL1, _FL2) similar pair
//     * (_FL3, _FL4) similar pair
// * 4 locked top layers (_LL1, _LL2, _LL3, _LL4)
//     * Access via: CK_LL1, CK_LL2, CK_LL3, CK_LL4, CK_UNLK
// * LEDs are lit according to the effective layer
//
enum layer_names {
    _BL1, // QWERTY base
    _BL2, // QWFRTY alternative
    _FL1, // Layer: F1-F10, 1-0, !-)
    _FL2, // Layer: F1-F10, 1-0, !-)
    _FL3, // Layer: other symbols
    _FL4, // Layer: other symbols
    _FL5, // Layer: Media, CK_LL1 - CK_LL4 (by combo(Q+P))
    _LL1, // cursor
    _LL2, // key pad (iso, jis)
    _LL3, // mouse
    _LL4  // internal configuration (RESET)
};

// All custom keycodes are after SAFE_RANGE
enum custom_keycodes {
    // lock-layers
    CK_LL1 = SAFE_RANGE ,
    CK_LL2,
    CK_LL3,
    CK_LL4,
    // unlock lock-layers
    CK_UNLK,
    // set default layer
    CK_BL1,
    CK_BL2,
    // mouse
    CK_M_UL,
    CK_M_UR,
    CK_M_DL,
    CK_M_DR,
    // ESC+CTRL_SPC (vim NORMAL MODE and set to English mode)
    CK_EENG,
    // ESC+TAB (input completion in mc/bash)
    CK_ETAB,
    // F4+UNLK (F4 to start mc editor mode with default layer)
    CK_UNF4
};

// define C macro for scripting aesthetics (7 chars max)

// Mod-Tap for home position finger keys
//   --- QWERTY
#define LS_A MT(MOD_LSFT, KC_A)
#define LC_S MT(MOD_LCTL, KC_S)
#define LA_D MT(MOD_LALT, KC_D)
#define LG_F MT(MOD_LGUI, KC_F)
#define RA_G MT(MOD_RALT, KC_G)
#define RA_H MT(MOD_RALT, KC_H)
#define LG_J MT(MOD_LGUI, KC_J)
#define LA_K MT(MOD_LALT, KC_K)
#define LC_L MT(MOD_LCTL, KC_L)
#define LS_SCLN MT(MOD_LSFT, KC_SCLN)
//   --- QWFRTY
#define LC_I MT(MOD_LCTL, KC_I)
#define LA_U MT(MOD_LALT, KC_U)
#define LG_E MT(MOD_LGUI, KC_E)
#define RA_O MT(MOD_RALT, KC_O)
#define RA_S MT(MOD_RALT, KC_S)
#define LG_H MT(MOD_LGUI, KC_H)
#define LA_J MT(MOD_LALT, KC_J)

// Momentarily Layer, Layer-Tap for thumb keys
#define K1_SPC LT(_FL1, KC_SPC)
#define K2_SPC LT(_FL2, KC_SPC)
#define K3_ESC LT(_FL3, KC_ESC)
#define K4_ENT LT(_FL4, KC_ENT)

// mc: ALT-P/ALT-N/ALT-ENT/CTL-U/CTL-R
#define KC_ALTP LALT(KC_P)
#define KC_ALTN LALT(KC_N)
#define KC_AENT LALT(KC_ENT)
#define KC_CTLU LCTL(KC_U)
#define KC_CTLR LCTL(KC_R)

// Select one of US/JP/ISO
//      KEYCODE HEX     us      US      iso     ISO     jis     JIS     かな
//      KC_NUHS  32     \       |       #       ~       ]       }
//      KC_NUBS  64     <       >       \       |
//      KC_INT1  87                                     \       _       ろ
//      KC_INT2  88                                     HIRAGANA/KATAKANA
//      KC_INT3  89     \       |                       \       |       ー
//      KC_INT4  8A                                     変換
//      KC_INT5  8B                                     無変換
//
// Input method support (CJK)
//   - KC_SSPC -- Romaji->Hiragana input mode
//   - KC_CSPC -- direct input mode
// If other input methods are in use, change these.
//
// US keyboard
#define KC_XXX1 XXXXXXX
#define KC_XXX2 XXXXXXX
#define KC_SXX1 XXXXXXX
#define KC_SXX2 XXXXXXX
#define KC_SSPC LSFT(KC_SPC)
#define KC_CSPC LCTL(KC_SPC)
// JP keyboard
//#define KC_XXX1 KC_INT1
//#define KC_XXX2 KC_INT3
//#define KC_SXX1 LSFT(KC_INT1)
//#define KC_SXX2 LSFT(KC_INT3)
//#define KC_SSPC KC_INT4
//#define KC_CSPC KC_INT5
// ISO keyboard
//#define KC_XXX1 KC_NUHS
//#define KC_XXX2 KC_NUBS
//#define KC_SXX1 LSFT(KC_NUHS)
//#define KC_SXX2 LSFT(KC_NUBS)
//#define KC_SSPC LSFT(KC_SPC)
//#define KC_CSPC LCTL(KC_SPC)

// For unlock caps ???
#define LS_CAPS LSFT(KC_CAPS)

// TRANS (pressed)
#define vvvvvvv KC_TRNS
// To be filled
#define KKKKKKK XXXXXXX

// This is meant to be the most finger friendly keymap using entire 4x14
// ortholinear keyboard
//
// This offers a minimum stress keymap with easy transition among:
//   - the standard TKL keyboard
//   - the ferris/sweep-like (3row * 5column + 2thumb) x2 split keyboard (drop 4 keys on both left and right sides; and 8 keys at the center)
//   - the planck-like 4x12 ortholinear keyboard (drop 4 keys on both left and right sides)
//   - the let's-split-like (4row * 6column) x2 split keyboard (drop 4 keys on both left and right sides)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ****************************************************************************************************************************************
     * QWERTY -- for normal typing
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ Q │ W │ E │ R │ T │ ` │ \ │ Y │ U │ I │ O │ P │BS │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ A │ S │ D │ F │ G │ [ │ ] │ H │ J │ K │ L │ ; │Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ _ │ ' │ N │ M │ , │ . │ / │Sft│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│Alt│Gui│LL1│Es3│Sp1│Spc│Spc│Sp2│En4│App│Gui│Agr│Ctl│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_BL1] = LAYOUT(
            KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_GRV,  KC_BSLS, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            KC_TAB,  LS_A,    LC_S,    LA_D,    LG_F,    RA_G,    KC_LBRC, KC_RBRC, RA_H,    LG_J,    LA_K,    LC_L,    LS_SCLN, KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_UNDS, KC_QUOT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_LCTL, KC_LALT, KC_LGUI, CK_LL1,  K3_ESC,  K1_SPC,  KC_SPC,  KC_SPC,  K2_SPC,  K4_ENT,  KC_APP,  KC_RGUI, KC_RALT, KC_RCTL
            ),

    /* ****************************************************************************************************************************************
     * QWFRTY -- for romaji-optimized typing in (n)vim
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ Q │ W │ F │ R │ T │ ` │ \ │ Y │ D │ K │ G │ P │BS │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ A │ I │ U │ E │ O │ [ │ ] │ S │ H │ J │ L │ ; │Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ _ │ ' │ N │ M │ , │ . │ / │Sft│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│Alt│Gui│LL1│Es3│Sp1│Spc│Spc│Sp2│En4│App│Gui│Agr│Ctl│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_BL2] = LAYOUT(
            KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_R,    KC_T,    KC_GRV,  KC_BSLS, KC_Y,    KC_D,    KC_K,    KC_G,    KC_P,    KC_BSPC,
            KC_TAB,  LS_A,    LC_I,    LA_U,    LG_E,    RA_O,    KC_LBRC, KC_RBRC, RA_S,    LG_H,    LA_J,    LC_L,    LS_SCLN, KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_UNDS, KC_QUOT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_LCTL, KC_LALT, KC_LGUI, CK_LL1,  K3_ESC,  K1_SPC,  KC_SPC,  KC_SPC,  K2_SPC,  K4_ENT,  KC_APP,  KC_RGUI, KC_RALT, KC_RCTL
            ),

    /* ****************************************************************************************************************************************
     * _FL1 (right side)
     * _FL2 (left side)
     *     High Function keys F1-F10 (F11, F12)
     *     MidH Normal shifted number keys
     *     MidL Normal number keys
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │***│F1 │F2 │F3 │F4 │F5 │F11│F12│F6 │F7 │F8 │F9 │F10│***│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│ ! │ @ │ # │ $ │ % │***│***│ ^ │ & │ * │ ( │ ) │***│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│ 1 │ 2 │ 3 │ 4 │ 5 │***│***│ 6 │ 7 │ 8 │ 9 │ 0 │***│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│***│***│***│CSP│BS │***│***│TAB│SSP│***│***│***│***│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_FL1] = LAYOUT(
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
            _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_RALT, DM_PLY1, DM_PLY2, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
            _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    DM_REC1, DM_REC2, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
            _______, _______, _______, _______, KC_CSPC, vvvvvvv, _______, _______, KC_TAB,  KC_SSPC, _______, _______, _______, _______
            ),
    [_FL2] = LAYOUT(
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
            _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, DM_PLY1, DM_PLY2, KC_RALT, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,
            _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    DM_REC1, DM_REC2, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
            _______, _______, _______, _______, KC_CSPC, KC_BSPC, _______, _______, vvvvvvv, KC_SSPC, _______, _______, _______, _______
            ),

    /* ****************************************************************************************************************************************
     * _FL3 (right side)
     * _FL4 (left side)
     *     High Function keys F11-F20
     *     MidH extra symbol keys shifted
     *     MidL extra symbol keys
     *     (Center columns Cursor keys)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │***│F11│F12│F13│F14│F15│***│***│F16│F17│F18│F19│F20│***│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│Cap│ ~ │   │ _ │ + │***│***│ { │ } │ | │   │ " │***│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│   │ ` │   │ - │ = │***│***│ [ │ ] │ \ │   │ ' │***│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│***│***│***│Ins│   │***│***│   │LL1│***│***│***│***│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_FL3] = LAYOUT(
            _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_INS,  KC_DEL,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
            _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_RALT, KC_HOME, KC_END,  KC_LCBR, KC_RCBR, KC_PIPE, KC_SXX2, KC_DQUO, _______,
            _______, LS_CAPS, KC_GRV,  KC_XXX1, KC_MINS, KC_EQL,  KC_PGUP, KC_UP,   KC_LBRC, KC_RBRC, KC_BSLS, KC_XXX2, KC_QUOT, _______,
            _______, _______, _______, _______, vvvvvvv, KC_LEFT, KC_PGDN, KC_DOWN, KC_RGHT, CK_LL1,  _______, _______, _______, _______
            ),
    [_FL4] = LAYOUT(
            _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_INS,  KC_DEL,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
            _______, KC_CAPS, KC_TILD, KC_SXX1, KC_UNDS, KC_PLUS, KC_HOME, KC_END,  KC_RALT, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,
            _______, LS_CAPS, KC_GRV,  KC_XXX1, KC_MINS, KC_EQL,  KC_PGUP, KC_UP,   KC_LBRC, KC_RBRC, KC_BSLS, KC_XXX2, KC_QUOT, _______,
            _______, _______, _______, _______, KC_INS,  KC_LEFT, KC_PGDN, KC_DOWN, KC_RGHT, vvvvvvv, _______, _______, _______, _______
            ),
    /* ****************************************************************************************************************************************
     * _FL5 (both Q+P pressed) -- non standard input keys (layer transition to hidden locked layers)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │***│vvv│   │Mut│VDN│VUP│***│***│LL1│LL2│LL3│LL4│vvv│***│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│   │   │   │   │   │***│***│   │   │   │   │   │***│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│   │   │   │   │   │***│***│   │   │   │   │   │***│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│***│***│***│   │   │***│***│   │   │***│***│***│***│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_FL5] = LAYOUT(
            _______, vvvvvvv, PB_1,    KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, CK_LL1,  CK_LL2,  CK_LL3,  CK_LL4,  vvvvvvv, _______,
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
            _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______
            ),


    /* ****************************************************************************************************************************************
     * Cursor locked layer (useful)  optimized to work with mc (midnight commander) and vim insert mode
     *    CK_ETAB: ESC and TAB          -- for mc for tab command line expansion
     *    CK_EENG: ESC and English mode -- for exiting insert mode of vim and set it English mode
     */
    [_LL1] = LAYOUT(
            _______, KC_F1,   KC_F2,   KC_F3,   CK_UNF4, KC_F5,   XXXXXXX, XXXXXXX, KC_INS,  KC_PGUP, KC_UP,   KC_PGDN, KC_DEL,  _______,
            _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_APP,  XXXXXXX, XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______,
            _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX, XXXXXXX, KC_CTLU, KC_ALTP, KC_TAB,  KC_ALTN, KC_CTLR, _______,
            _______, _______, _______, _______, CK_EENG, CK_UNLK, CK_UNLK, CK_UNLK, CK_ETAB, KC_ENT,  _______, _______, _______, _______
            ),

    /* ****************************************************************************************************************************************
     * Numpad locked layer: Numpad dynamic macro
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │___│___│___│___│___│___│___│___│ - │ 7 │ 8 │ 9 │BS │___│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │___│___│___│___│___│___│___│___│ * │ 4 │ 5 │ 6 │ + │___│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │___│___│___│___│___│___│___│___│ / │ 1 │ 2 │ 3 │PEn│___│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │___│___│___│___│___│___│___│___│ . │ 0 │ 0 │ . │PEn│___│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     * All off-main area (numpad etc.)
     */
    [_LL2] = LAYOUT(
            _______, KKKKKKK, KC_SCRL, KC_PAUS, KC_PSCR, KC_NUM,  XXXXXXX, XXXXXXX, KC_PMNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_BSPC, _______,
            _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_APP,  XXXXXXX, XXXXXXX, KC_PAST, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,
            _______, DM_REC1, DM_REC2, DM_RSTP, DM_PLY1, DM_PLY2, XXXXXXX, XXXXXXX, KC_PSLS, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______,
            _______, _______, _______, _______, CK_UNLK, CK_UNLK, CK_UNLK, CK_UNLK, KC_DOT,  KC_KP_0, KC_KP_0, KC_DOT,  KC_PENT, _______
            ),

    /* ****************************************************************************************************************************************
     * Mouse locked layer: mouse keys (mostly useless)
     */
    [_LL3] = LAYOUT(
            _______, KC_BTN4, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN5, XXXXXXX, XXXXXXX, KC_WH_U, CK_M_UL, KC_MS_U, CK_M_UR, KC_BSPC, _______,
            _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_APP,  XXXXXXX, XXXXXXX, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, _______,
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_D, CK_M_DL, KC_MS_D, CK_M_DR, XXXXXXX, _______,
            _______, _______, _______, _______, CK_UNLK, CK_UNLK, CK_UNLK, CK_UNLK, KKKKKKK, KC_ENT,  KC_BTN1, KC_BTN2, KC_BTN3, _______
            ),
    /* ****************************************************************************************************************************************
     * INTERNAL use locked layerd (for reset to reprogram)
     * Basically internal configuration keys
     */
    [_LL4] = LAYOUT(
            _______, EC_TOGG, KKKKKKK, CK_UP,   CK_ON,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NK_ON,   XXXXXXX, EE_CLR,  QK_BOOT, _______,
            _______, CK_BL1,  CK_BL2,  CK_RST,  CK_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DB_TOGG, _______,
            _______, KKKKKKK, KKKKKKK, CK_DOWN, CK_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NK_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
            _______, _______, _______, _______, CK_UNLK, CK_UNLK, CK_UNLK, CK_UNLK, KKKKKKK, KKKKKKK, _______, _______, _______, _______
            ),
};


// There is a limit for total DC current of IC to be 200 mA. (or 100mA for
// each port group, 40mA for each PIN).
//
// I have 4 of 2-color LEDs with each limiting to 18mA, turning all of them
// cause to consume 144 mA.

// LED_P_RED_PIN is used for indicating keyboard internal state
// Its blinks indicate default layer to be used when it is set
// Other RED pins are for Caps/Scroll/Num Locks

void fn_led_blinks(uint8_t blinks) {
    for (uint8_t n = 0; n < blinks; n++) {
        fn_led_of(LED_P_RED_PIN);
        wait_ms(50);
        fn_led_on(LED_P_RED_PIN);
        wait_ms(150);
    }
    return;
}

// Continuous LED on/off indicates highest active layer
// 4 BLUE LEDs and 1 RED LED used
// Other RED pins are for Caps/Scroll/Num Locks
layer_state_t layer_state_set_kb(layer_state_t orig_state) {
    layer_state_t state = layer_state_set_user(orig_state);
    // check from MSB -> LSB
    if (state & (1L << _LL4))
    {
        // B*___*R*..*
        fn_led_on(LED_Q_BLU_PIN);
        fn_led_of(LED_T_BLU_PIN);
        fn_led_of(LED_Y_BLU_PIN);
        fn_led_on(LED_P_BLU_PIN);
        fn_led_on(LED_Q_RED_PIN);
        fn_led_on(LED_P_RED_PIN);
    } else if (state & (1L << _LL3))
    {
        // B_*** R*.._
        fn_led_of(LED_Q_BLU_PIN);
        fn_led_on(LED_T_BLU_PIN);
        fn_led_on(LED_Y_BLU_PIN);
        fn_led_on(LED_P_BLU_PIN);
        fn_led_on(LED_Q_RED_PIN);
        fn_led_of(LED_P_RED_PIN);
    } else if (state & (1L << _LL2))
    {
        // B***_ R_..*
        fn_led_on(LED_Q_BLU_PIN);
        fn_led_on(LED_T_BLU_PIN);
        fn_led_on(LED_Y_BLU_PIN);
        fn_led_of(LED_P_BLU_PIN);
        fn_led_of(LED_Q_RED_PIN);
        fn_led_on(LED_P_RED_PIN);
    } else if (state & (1L << _LL1))
    {
        // B_**_ R*..*
        fn_led_of(LED_Q_BLU_PIN);
        fn_led_on(LED_T_BLU_PIN);
        fn_led_on(LED_Y_BLU_PIN);
        fn_led_of(LED_P_BLU_PIN);
        fn_led_on(LED_Q_RED_PIN);
        fn_led_on(LED_P_RED_PIN);
    //////////////////////////////
    } else if (state & (1L << _FL5))
    {
        // B____ R*..*
        fn_led_of(LED_Q_BLU_PIN);
        fn_led_of(LED_T_BLU_PIN);
        fn_led_of(LED_Y_BLU_PIN);
        fn_led_of(LED_P_BLU_PIN);
        fn_led_on(LED_Q_RED_PIN);
        fn_led_on(LED_P_RED_PIN);
    } else if (state & (1L << _FL4))
    {
        // B__** R_.._
        fn_led_of(LED_Q_BLU_PIN);
        fn_led_of(LED_T_BLU_PIN);
        fn_led_on(LED_Y_BLU_PIN);
        fn_led_on(LED_P_BLU_PIN);
        fn_led_of(LED_Q_RED_PIN);
        fn_led_of(LED_P_RED_PIN);
    } else if (state & (1L << _FL3))
    {
        // B**__ R_.._
        fn_led_on(LED_Q_BLU_PIN);
        fn_led_on(LED_T_BLU_PIN);
        fn_led_of(LED_Y_BLU_PIN);
        fn_led_of(LED_P_BLU_PIN);
        fn_led_of(LED_Q_RED_PIN);
        fn_led_of(LED_P_RED_PIN);
    } else if (state & (1L << _FL2))
    {
        // B__*_ R_..*
        fn_led_of(LED_Q_BLU_PIN);
        fn_led_of(LED_T_BLU_PIN);
        fn_led_on(LED_Y_BLU_PIN);
        fn_led_of(LED_P_BLU_PIN);
        fn_led_of(LED_Q_RED_PIN);
        fn_led_on(LED_P_RED_PIN);
    } else if (state & (1L << _FL1))
    {
        // B_*__ R*.._
        fn_led_of(LED_Q_BLU_PIN);
        fn_led_on(LED_T_BLU_PIN);
        fn_led_of(LED_Y_BLU_PIN);
        fn_led_of(LED_P_BLU_PIN);
        fn_led_on(LED_Q_RED_PIN);
        fn_led_of(LED_P_RED_PIN);
    } else // No-Fn pressed
    {
        switch(get_highest_layer(default_layer_state))
        {
            case _BL2:
                // B_**_ R_.._
                fn_led_of(LED_Q_BLU_PIN);
                fn_led_on(LED_T_BLU_PIN);
                fn_led_on(LED_Y_BLU_PIN);
                fn_led_of(LED_P_BLU_PIN);
                fn_led_of(LED_Q_RED_PIN);
                fn_led_of(LED_P_RED_PIN);
                break;
            default:
                // B**** R_.._
                fn_led_on(LED_Q_BLU_PIN);
                fn_led_on(LED_T_BLU_PIN);
                fn_led_on(LED_Y_BLU_PIN);
                fn_led_on(LED_P_BLU_PIN);
                fn_led_of(LED_Q_RED_PIN);
                fn_led_of(LED_P_RED_PIN);
                break;
        }
    }
    return state ;
}

// define macro actions for mouse keys
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch(keycode)
    {
        case CK_BL1:
            if (record->event.pressed)
            {
                // just to be safe side
                layer_on(_BL1);
                layer_off(_BL2);
                // normal setting
                set_single_persistent_default_layer(_BL1);
                fn_led_blinks(1);
            }
            return false;
            break;

        case CK_BL2:
            if (record->event.pressed)
            {
                set_single_persistent_default_layer(_BL2);
                fn_led_blinks(2);
            }
            return false;
            break;

        case CK_UNLK:
            if (record->event.pressed)
            {
                layer_off(_LL1);
                layer_off(_LL2);
                layer_off(_LL3);
                layer_off(_LL4);
            }
            return false;
            break;

        case CK_LL1:
            if (record->event.pressed)
            {
                layer_on(_LL1);
                layer_off(_LL2);
                layer_off(_LL3);
                layer_off(_LL4);
            }
            return false;
            break;

        case CK_LL2:
            if (record->event.pressed)
            {
                layer_on(_LL2);
                layer_off(_LL1);
                layer_off(_LL3);
                layer_off(_LL4);
            }
            return false;
            break;

        case CK_LL3:
            if (record->event.pressed)
            {
                layer_on(_LL3);
                layer_off(_LL1);
                layer_off(_LL2);
                layer_off(_LL4);
            }
            return false;
            break;

        case CK_LL4:
            if (record->event.pressed)
            {
                layer_on(_LL4);
                layer_off(_LL1);
                layer_off(_LL2);
                layer_off(_LL3);
            }
            return false;
            break;

        case CK_M_UL:
            if (record->event.pressed)
            {
                register_code(KC_MS_UP);
                register_code(KC_MS_LEFT);
            }
            else
            {
                unregister_code(KC_MS_LEFT);
                unregister_code(KC_MS_UP);
            }
            return false;
            break;

        case CK_M_UR:
            if (record->event.pressed)
            {
                register_code(KC_MS_UP);
                register_code(KC_MS_RIGHT);
            }
            else
            {
                unregister_code(KC_MS_RIGHT);
                unregister_code(KC_MS_UP);
            }
            return false;
            break;

        case CK_M_DL:
            if (record->event.pressed)
            {
                register_code(KC_MS_DOWN);
                register_code(KC_MS_LEFT);
            }
            else
            {
                unregister_code(KC_MS_LEFT);
                unregister_code(KC_MS_DOWN);
            }
            return false;
            break;

        case CK_M_DR:
            if (record->event.pressed)
            {
                register_code(KC_MS_DOWN);
                register_code(KC_MS_RIGHT);
            }
            else
            {
                unregister_code(KC_MS_RIGHT);
                unregister_code(KC_MS_DOWN);
            }
            return false;
            break;

        case PB_1:
            if (record->event.pressed)
            {
                SEND_STRING("uname -a\n");
            }
            else
            {
                SEND_STRING("Hello from: osamu at debian.org, using  QMK GPL firmware.\n");
            }
            return false;
            break;

        case CK_EENG:
            if (record->event.pressed)
            {
                register_code(KC_ESC);
            }
            else
            {
                unregister_code(KC_ESC);
                // vim focused trick
                register_code(KC_LCTRL);
                register_code(KC_SPC);
                unregister_code(KC_SPC);
                unregister_code(KC_LCTRL);
            }
            return false;
            break;

        case CK_ETAB:
            if (record->event.pressed)
            {
                register_code(KC_ESC);
            }
            else
            {
                unregister_code(KC_ESC);
                // mc focused trick
                register_code(KC_TAB);
                unregister_code(KC_TAB);
            }
            return false;
            break;

        case CK_UNF4:
            if (record->event.pressed)
            {
                register_code(KC_F4);
            }
            else
            {
                unregister_code(KC_F4);
                layer_off(_LL1);
                layer_off(_LL2);
                layer_off(_LL3);
                layer_off(_LL4);
            }
            return false;
            break;

        default:
            break;

    }
    return true;
};

// Combo to access _FL5
const uint16_t PROGMEM qp_combo[] = {KC_Q, KC_P, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(qp_combo, MO(_FL5)),
};

