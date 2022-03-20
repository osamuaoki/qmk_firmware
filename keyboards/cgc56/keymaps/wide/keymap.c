// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=128 sts=4 ts=24 sw=4 et ai:
#include QMK_KEYBOARD_H
#include "wait.h"

// This is a programmable keyboard with 10 layers:
// * 2 choices for the default layer (_BL1, _BL2)
// * 4 temporary top layers (_FL1, _FL2, _FL3, _FL4)
// * 3 locked top layers (_FL5, _FL6, _FL7)
//     * Access via: CK_LL5, CK_LL6, CK_LL7, CK_UNLK
// * LEDs are lit according to the effective layer
//
enum layer_names {
    _BL1, // QWERTY base
    _BL2, // QWFRTY alternative
    _FL1, // Layer: F1-F10, 1-0, symbols
    _FL2, // Layer: F1-F10, 1-0, symbols (almost duplicate)
    _FL3, // Layer: cursor keys
    _FL4, // Layer: cursor keys (almost duplicate)
    _FL5, // Layer: cursor keys (almost duplicate) -- locked
    _FL6, // numpad                                -- locked
    _FL7  // internal configuration                -- locked
};

// All custom keycodes are after SAFE_RANGE
enum custom_keycodes {
    // lock-layers
    CK_LL5 = SAFE_RANGE,
    CK_LL6,
    CK_LL7,
    // unlock lock-layers
    CK_UNLK,
    // set default layer
    CK_BL1,
    CK_BL2,
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
//#define MO3 MO(_FL3)
#define MO3 LT(_FL3, KC_ESC)
//#define MO4 MO(_FL4)
#define MO4 LT(_FL4, KC_BSPC)

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
// US keyboard
#define KC_XXX1 XXXXXXX
#define KC_XXX2 XXXXXXX
#define KC_SXX1 XXXXXXX
#define KC_SXX2 XXXXXXX
// JP keyboard
//#define KC_XXX1 KC_INT1
//#define KC_XXX2 KC_INT3
//#define KC_SXX1 LSFT(KC_INT1)
//#define KC_SXX2 LSFT(KC_INT3)
// ISO keyboard
//#define KC_XXX1 KC_NUHS
//#define KC_XXX2 KC_NUBS
//#define KC_SXX1 LSFT(KC_NUHS)
//#define KC_SXX2 LSFT(KC_NUBS)

// For unlock caps ???
#define LS_CAPS LSFT(KC_CAPS)

// TRANS (pressed)
#define vvvvvvv KC_TRNS
// To be filled
#define KKKKKKK XXXXXXX
#define KC_XXXX XXXXXXX

// This is meant to be the most finger friendly keymap using entire 4x14
// ortholinear keyboard
//
// This offers a minimum stress keymap with easy transition among:
//   - the standard TKL keyboard
//   - the ferris/sweep-like (3row * 5column + 2thumb) x2 split keyboard (drop 16 keys at the center)
//   - the planck-like 4x12 ortholinear keyboard
//   - the let's-split-like (4row * 6column) x2 split keyboard

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ****************************************************************************************************************************************
     * QWERTY -- for normal typing
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ Q │ W │ E │ R │ T │Ins│Cap│Num│Del│ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │ ￩ │PL1│PL2│ ￫ │ H │ J │ K │ L │ ; │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │ ￪ │RE1│RE2│ ￬ │ N │ M │ , │ . │ / │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Spc│GUI│LL6│MO3│Sp1│Tab│Spc│Spc│Ent│En2│MO4│LL5│APP│Spc│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_BL1] = LAYOUT(
            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_INS,  KC_CAPS, KC_NUM,  KC_DEL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
            LS_A,    LC_S,    LA_D,    LG_F,    RA_G,    KC_LEFT, DM_PLY1, DM_PLY2, KC_RGHT, RA_H,    LG_J,    LA_K,    LC_L,    LS_SCLN,
            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_UP,   DM_REC1, DM_REC2, KC_DOWN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
            KC_SPC,  KC_LGUI, CK_LL6,  MO3,     K1_SPC,  KC_TAB,  KC_SPC,  KC_SPC,  KC_ENT,  K2_SPC,  MO4,     CK_LL5,  KC_APP,  KC_SPC
            ),

    /* ****************************************************************************************************************************************
     * QWFRTY -- for romaji-optimized typing in (n)vim
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ Q │ W │ F │ R │ T │Ins│Cap│Num│Del│ Y │ D │ K │ G │ P │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ I │ U │ E │ O │ ￩ │PL1│PL2│ ￫ │ S │ H │ J │ L │ ; │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │ ￪ │RE1│RE2│ ￬ │ N │ M │ , │ . │ / │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Spc│GUI│LL6│MO3│Sp1│Tab│Spc│Spc│Ent│En2│MO4│LL5│APP│Spc│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_BL2] = LAYOUT(
            KC_Q,    KC_W,    KC_F,    KC_R,    KC_T,    KC_INS,  KC_CAPS, KC_NUM,  KC_DEL,  KC_Y,    KC_D,    KC_K,    KC_G,    KC_P,
            LS_A,    LC_I,    LA_U,    LG_E,    RA_O,    KC_LEFT, DM_PLY1, DM_PLY2, KC_RGHT, RA_S,    LG_H,    LA_J,    LC_L,    LS_SCLN,
            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_UP,   DM_REC1, DM_REC2, KC_DOWN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
            KC_SPC,  KC_LGUI, CK_LL6,  MO3,     K1_SPC,  KC_TAB,  KC_SPC,  KC_SPC,  KC_ENT,  K2_SPC,  MO4,     CK_LL5,  KC_APP,  KC_SPC
            ),

    /* ****************************************************************************************************************************************
     * _FL1 (right side)
     * _FL2 (left side)
     *     High Function keys F1-F10 (F11, F12)
     *     MidH Normal shifted number keys
     *     MidL Normal number keys
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │F1 │F2 │F3 │F4 │F5 │F11│Cap│Num│F12│F6 │F7 │F8 │F9 │F10│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ 4 │ 5 │Hom│***│***│End│ 6 │ 7 │ 8 │ 9 │ 0 │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Cap│ ~ │   │ - │ = │PgU│***│***│PgD│ [ │ ] │ \ │   │ ' │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│***│***│Esc│Spc│Tab│Spc│Spc│Ent│Spc│Bs │***│***│***│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_FL1] = LAYOUT(
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  _______, _______, KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
            KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_RALT, KC_HOME, _______, _______, KC_END,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
            LS_CAPS, KC_GRV,  KC_XXX1, KC_MINS, KC_EQL,  KC_PGUP, _______, _______, KC_PGDN, KC_LBRC, KC_RBRC, KC_BSLS, KC_XXX2, KC_QUOT,
            _______, _______, _______, XXXXXXX, vvvvvvv, XXXXXXX, _______, _______, KC_ENT,  KC_SPC,  KC_BSPC, _______, _______, _______
            ),
    [_FL2] = LAYOUT(
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  _______, _______, KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME, _______, _______, KC_END,  KC_RALT, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,
            LS_CAPS, KC_GRV,  KC_XXX1, KC_MINS, KC_EQL,  KC_PGUP, _______, _______, KC_PGDN, KC_LBRC, KC_RBRC, KC_BSLS, KC_XXX2, KC_QUOT,
            _______, _______, _______, CK_EENG, KC_SPC,  KC_TAB,  _______, _______, XXXXXXX, vvvvvvv, XXXXXXX, _______, _______, _______
            ),

    /* ****************************************************************************************************************************************
     * Cursor layer (temporary and locked) and macro
     *     Right highs: cursors
     *     High Function keys F11-F12 (left)
     *     MidH Layer/mod operation (left)
     *     MidL extra symbol keys
     *     (Center columns Cursor keys)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │F11│F12│   │F4e│   │***│***│***│***│PgU│Hm │ ￪ │End│Ins│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │BL1│BL2│LL7│LL6│LL5│***│***│***│***│PgD│ ￩ │ ￬ │ ￫ │Del│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │RC1│RC2│PL1│PL2│   │***│***│***│***│Tab│Psc│Scr│Pau│App│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│***│***│vvv│UNL│***│***│***│***│   │vvv│***│***│***│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_FL3] = LAYOUT(
            KC_F11,  KC_F12,  KC_F3,   CK_UNF4, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_INS,
            KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, CK_LL5,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,
            DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TAB,  KC_PSCR, KC_SCRL, KC_PAUS, KC_APP,
            _______, _______, _______, vvvvvvv, KC_SPC,  CK_ETAB, KC_SPC,  KC_SPC,  KC_ENT,  KC_SPC,  KC_BSPC, _______, _______, _______
            ),
    [_FL4] = LAYOUT(
            KC_F11,  KC_F12,  KC_F3,   CK_UNF4, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_INS,
            CK_BL1,  CK_BL2,  CK_LL7,  CK_LL6,  CK_LL5,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,
            DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TAB,  KC_PSCR, KC_SCRL, KC_PAUS, KC_APP,
            _______, _______, _______, CK_EENG, KC_SPC,  CK_ETAB, KC_SPC,  KC_SPC,  KC_ENT,  KC_SPC,  vvvvvvv, _______, _______, _______
            ),
    [_FL5] = LAYOUT(
            KC_F1,   KC_F2,   KC_F3,   CK_UNF4, KC_F5,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_INS,
            KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, CK_UNLK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TAB,  KC_PSCR, KC_SCRL, KC_PAUS, KC_APP,
            _______, _______, _______, CK_EENG, CK_UNLK, CK_ETAB, KC_SPC,  KC_SPC,  KC_ENT,  KC_SPC,  KC_BSPC, _______, _______, _______
            ),

    /* ****************************************************************************************************************************************
     * Numpad locked layer: Numpad/media
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │___│___│___│___│___│___│___│___│___│ - │ 7 │ 8 │ 9 │BS │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │___│___│___│___│___│___│___│___│___│ * │ 4 │ 5 │ 6 │ + │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │___│___│___│___│___│___│___│___│___│ / │ 1 │ 2 │ 3 │PEn│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │___│___│___│___│___│___│___│___│___│ . │ 0 │ 0 │ . │PEn│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     * All off-main area (numpad etc.)
     */
    [_FL6] = LAYOUT(
            XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, KC_CAPS, KC_NUM,  XXXXXXX, KC_PMNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_BSPC,
            KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NUM,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAST, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSLS, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT,
            _______, _______, _______, KC_ESC,  CK_UNLK, KC_TAB,  KC_SPC,  KC_SPC,  KC_ENT,  KC_DOT,  KC_KP_0, KC_KP_0, KC_DOT,  KC_PENT
            ),

    /* ****************************************************************************************************************************************
     * Internal
     */
    [_FL7] = LAYOUT(
            EC_TOGG, XXXXXXX, CK_ON,   NK_ON,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,  QK_BOOT,
            XXXXXXX, XXXXXXX, CK_OFF,  NK_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            _______, _______, _______, XXXXXXX, CK_UNLK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
    if (state & (1L << _FL7))
    {
        // B*___* R*..*
        fn_led_on(LED_Q_BLU_PIN);
        fn_led_of(LED_T_BLU_PIN);
        fn_led_of(LED_Y_BLU_PIN);
        fn_led_on(LED_P_BLU_PIN);
        fn_led_on(LED_Q_RED_PIN);
        fn_led_on(LED_P_RED_PIN);
    } else if (state & (1L << _FL6))
    {
        // B_*** R*.._
        fn_led_of(LED_Q_BLU_PIN);
        fn_led_on(LED_T_BLU_PIN);
        fn_led_on(LED_Y_BLU_PIN);
        fn_led_on(LED_P_BLU_PIN);
        fn_led_on(LED_Q_RED_PIN);
        fn_led_of(LED_P_RED_PIN);
    } else if (state & (1L << _FL5))
    {
        // B***_ R_..*
        fn_led_on(LED_Q_BLU_PIN);
        fn_led_on(LED_T_BLU_PIN);
        fn_led_on(LED_Y_BLU_PIN);
        fn_led_of(LED_P_BLU_PIN);
        fn_led_of(LED_Q_RED_PIN);
        fn_led_on(LED_P_RED_PIN);
    //////////////////////////////
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
                layer_off(_FL3);
                layer_off(_FL5);
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
                layer_off(_FL5);
                layer_off(_FL6);
                layer_off(_FL7);
            }
            return false;
            break;

        case CK_LL5:
            if (record->event.pressed)
            {
                layer_on(_FL5);
                layer_off(_FL6);
                layer_off(_FL7);
            }
            return false;
            break;

        case CK_LL6:
            if (record->event.pressed)
            {
                layer_on(_FL6);
                layer_off(_FL5);
                layer_off(_FL7);
            }
            return false;
            break;

        case CK_LL7:
            if (record->event.pressed)
            {
                layer_on(_FL7);
                layer_off(_FL5);
                layer_off(_FL6);
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
                layer_off(_FL5);
                layer_off(_FL6);
                layer_off(_FL7);
            }
            return false;
            break;

        default:
            break;

    }
    return true;
};

// Combo to access to boot (w/o erasing memory)
const uint16_t PROGMEM qp_combo[] = {KC_Q, KC_P, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(qp_combo, QK_BOOT),
};

