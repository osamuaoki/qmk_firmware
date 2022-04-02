// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=128 sts=4 ts=24 sw=4 et ai:
#include QMK_KEYBOARD_H
#include "wait.h"
#include "joystick.h"
#include "analog.h"
#include "pointing_device.h"

// This is a programmable keyboard with 10 layers:
// * 2 choices for the default layer (_BL1, _BL2)
// * 2 temporary top layers (_FL1, _FL2)
// * 2 locked top layers (_FL3, _FL4)
//     * Access via: CK_LL3, CK_LL4, CK_UNLK
// * LEDs are lit according to the effective layer
//
enum layer_names {
    _BL1, // QWERTY base
    _BL2, // QWFRTY alternative
    _FL1, // Layer: F1-F10, 1-0, symbols
    _FL2, // Layer: F1-F10, 1-0, symbols (almost duplicate)
    _FL3, // numpad                                -- locked
    _FL4  // internal configuration                -- locked
};

// All custom keycodes are after SAFE_RANGE
enum custom_keycodes {
    // lock-layers
    CK_LL3 = SAFE_RANGE,
    CK_LL4,
    // unlock lock-layers
    CK_UNLK,
    // set default layer
    CK_BL1,
    CK_BL2,
    // ESC+CTRL_SPC (vim NORMAL MODE and set to English mode)
    CK_EENG,
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
#define RC_L MT(MOD_RCTL, KC_L)
#define RS_SCLN MT(MOD_RSFT, KC_SCLN)
//   --- QWFRTY
#define LC_I MT(MOD_LCTL, KC_I)
#define LA_U MT(MOD_LALT, KC_U)
#define LG_E MT(MOD_LGUI, KC_E)
#define RA_O MT(MOD_RALT, KC_O)
#define RA_S MT(MOD_RALT, KC_S)
#define LG_H MT(MOD_LGUI, KC_H)
#define LA_J MT(MOD_LALT, KC_J)
//  --- number
#define LS_1 MT(MOD_LSFT, KC_1)
#define LC_2 MT(MOD_LCTL, KC_2)
#define LA_3 MT(MOD_LALT, KC_3)
#define LG_4 MT(MOD_LGUI, KC_4)
#define RA_5 MT(MOD_RALT, KC_5)
#define RA_6 MT(MOD_RALT, KC_6)
#define LG_7 MT(MOD_LGUI, KC_7)
#define LA_8 MT(MOD_LALT, KC_8)
#define RC_9 MT(MOD_RCTL, KC_9)
#define RS_0 MT(MOD_RSFT, KC_0)

// Momentarily Layer, Layer-Tap for thumb keys
#define K1_SPC LT(_FL1, KC_SPC)
#define K2_SPC LT(_FL2, KC_SPC)

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
//#define KBDTYPE_US
#define KBDTYPE_USJP
//#define KBDTYPE_USISO
#ifdef KBDTYPE_US
// US only keyboard
#define KC_XXX1 XXXXXXX
#define KC_XXX2 XXXXXXX
#define KC_XXX3 XXXXXXX
#define KC_XXX4 XXXXXXX
#define KC_XXX5 XXXXXXX
#endif
#ifdef KBDTYPE_USJP
// US and JP keyboard
#define KC_XXX1 KC_INT1
#define KC_XXX2 KC_INT2
#define KC_XXX3 KC_INT3
#define KC_XXX4 KC_INT4
#define KC_XXX5 KC_INT5
#endif
#ifdef KBDTYPE_USISO
// ISO keyboard
#define KC_XXX1 KC_NUHS
#define KC_XXX2 XXXXXXX
#define KC_XXX3 KC_NUBS
#define KC_XXX4 XXXXXXX
#define KC_XXX5 XXXXXXX
#endif

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
     * │Esc│ Q │ W │ E │ R │ T │Ins│Del│ Y │ U │ I │ O │ P │Bs │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ A │ S │ D │ F │ G │ ￩ │ ￫ │ H │ J │ K │ L │ ; │Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ ￪ │ ￬ │ N │ M │ , │ . │ / │Sft│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │MB1│MB2│MB3│LL3│Esc│Sp1│Tab│Ent│En2│Bs │Psc│AGr│App│Crl│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_BL1] = LAYOUT(
            KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_INS,  KC_DEL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            KC_TAB,  LS_A,    LC_S,    LA_D,    LG_F,    RA_G,    KC_LEFT, KC_RGHT, RA_H,    LG_J,    LA_K,    RC_L,    RS_SCLN, KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_UP,   KC_DOWN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_BTN1, KC_BTN2, KC_BTN3, CK_LL3,  KC_ESC,  K1_SPC,  KC_TAB,  KC_ENT,  K2_SPC,  KC_BSPC, KC_PSCR, KC_RALT, KC_BTN6, KC_BTN5
            ),

    /* ****************************************************************************************************************************************
     * QWFRTY -- for romaji-optimized typing in (n)vim
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ Q │ W │ F │ R │ T │Ins│Del│ Y │ D │ K │ G │ P │Bs │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ A │ I │ U │ E │ O │ ￩ │ ￫ │ S │ H │ J │ L │ ; │Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ ￪ │ ￬ │ N │ M │ , │ . │ / │Sft│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │MB1│MB2│MB3│LL3│Esc│Sp1│Tab│Ent│En2│Bs │Psc│AGr│App│Crl│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_BL2] = LAYOUT(
            KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_R,    KC_T,    KC_INS,  KC_DEL,  KC_Y,    KC_D,    KC_K,    KC_G,    KC_P,    KC_BSPC,
            KC_TAB,  LS_A,    LC_I,    LA_U,    LG_E,    RA_O,    KC_LEFT, KC_RGHT, RA_S,    LG_H,    LA_J,    RC_L,    RS_SCLN, KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_UP,   KC_DOWN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_BTN1, KC_BTN2, KC_BTN3, CK_LL3,  KC_ESC,  K1_SPC,  KC_TAB,  KC_ENT,  K2_SPC,  KC_BSPC, KC_PSCR, KC_RALT, KC_BTN6, KC_BTN5
            ),

    /* ****************************************************************************************************************************************
     * _FL1 (right side)
     * _FL2 (left side)
     *     High Function keys F1-F10 (F11, F12)
     *     MidH Normal shifted number keys
     *     MidL Normal number keys
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│F1 │F2 │F3 │F4 │F5 │F11│F12│F6 │F7 │F8 │F9 │F10│Bs │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│ 1 │ 2 │ 3 │ 4 │ 5 │Hom│End│ 6 │ 7 │ 8 │ 9 │ 0 │Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│Cap│ ~ │ー │ - │ = │PgU│PgD│ [ │ ] │ \ │ろ │ ' │Sft│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │***│***│***│LL4│Esc│LL3│xx5│xx4│Psc│xx2│Mut│***│***│***│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_FL1] = LAYOUT(
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
            _______, LS_1,    LC_2,    LA_3,    LG_4,    RA_5,    KC_HOME, KC_END,  RA_6,    LG_7,    LA_8,    RC_9,    RS_0,    _______,
            _______, LS_CAPS, KC_GRV,  KC_XXX3, KC_MINS, KC_EQL,  KC_PGUP, KC_PGDN, KC_LBRC, KC_RBRC, KC_BSLS, KC_XXX1, KC_QUOT, _______,
            _______, _______, _______, CK_LL4,  CK_EENG, vvvvvvv, KC_XXX5, KC_XXX4, KC_PSCR, KC_XXX2, KC_MUTE, _______, _______, _______
            ),
    [_FL2] = LAYOUT(
            _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
            _______, LS_1,    LC_2,    LA_3,    LG_4,    RA_5,    KC_HOME, KC_END,  RA_6,    LG_7,    LA_8,    RC_9,    RS_0,    _______,
            _______, LS_CAPS, KC_GRV,  KC_XXX3, KC_MINS, KC_EQL,  KC_PGUP, KC_PGDN, KC_LBRC, KC_RBRC, KC_BSLS, KC_XXX1, KC_QUOT, _______,
            _______, _______, _______, CK_LL4,  CK_EENG, CK_LL3,  KC_XXX5, KC_XXX4, vvvvvvv, KC_XXX2, KC_MUTE, _______, _______, _______
            ),

    /* ****************************************************************************************************************************************
     * Numpad locked layer: Numpad/media
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │___│Mut│Vup│Vdn│BL1│BL2│Psc│Num│ - │ 7 │ 8 │ 9 │BS │___│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │___│Sft│Ctl│Alt│Gui│LL4│Scr│Cal│ * │ 4 │ 5 │ 6 │ + │___│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │___│RE1│RE2│PL1│PL2│APP│Pau│ = │ / │ 1 │ 2 │ 3 │PEn│___│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │___│___│___│___│___│___│___│Ent│ . │ 0 │ 0 │ . │PEn│___│
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     * All off-main area (numpad etc.)
     */
    [_FL3] = LAYOUT(
            _______, KC_MUTE, KC_VOLD, KC_VOLU, CK_BL1,  CK_BL2,  KC_PSCR, KC_NUM,  KC_PMNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_BSPC, _______,
            _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, CK_LL4,  KC_SCRL, KC_CALC, KC_PAST, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,
            _______, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, KC_APP,  KC_PAUS, KC_PEQL, KC_PSLS, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, _______,
            _______, _______, _______, _______, KC_ESC,  CK_UNLK, KC_TAB,  KC_ENT,  KC_PDOT, KC_KP_0, KC_KP_0, KC_PDOT, KC_PENT, _______
            ),

    /* ****************************************************************************************************************************************
     * Internal
     */
    [_FL4] = LAYOUT(
            _______, EC_TOGG, XXXXXXX, CK_ON,   NK_ON,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DB_TOGG, EE_CLR,  QK_BOOT, _______,
            _______, XXXXXXX, XXXXXXX, CK_OFF,  NK_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
            _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
            _______, _______, _______, _______, XXXXXXX, CK_UNLK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
            ),

};

// LED_BLUE is used for indicating keyboard internal state
// Its blinks indicate default layer to be used when it is set

void fn_led_blinks(uint8_t blinks) {
    for (uint8_t n = 0; n < blinks; n++) {
        fn_led_of(LED_BLUE);
        wait_ms(50);
        fn_led_on(LED_BLUE);
        wait_ms(150);
    }
    fn_led_of(LED_BLUE);
    wait_ms(50);
    return;
}

void keyboard_post_init_user(void) {
  // Customize these values to desired behavior
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}

layer_state_t layer_state_set_kb(layer_state_t orig_state) {
    layer_state_t state = layer_state_set_user(orig_state);
    // check from MSB -> LSB
    if (state & ((1L << _FL4) | (1L << _FL3)))
    {
        fn_led_on(LED_BLUE);
    } else // Not-in-lockedLayetr
    {
        fn_led_of(LED_BLUE);
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
                fn_led_blinks(1);
                // normal setting
                set_single_persistent_default_layer(_BL1);
                // just to be safe side
                layer_on(_BL1);
                layer_off(_BL2);
                layer_off(_FL3);
                layer_off(_FL4);
            }
            return false;
            break;

        case CK_BL2:
            if (record->event.pressed)
            {
                fn_led_blinks(2);
                // normal setting
                set_single_persistent_default_layer(_BL2);
                // just to be safe side
                layer_off(_BL1);
                layer_on(_BL2);
                layer_off(_FL3);
                layer_off(_FL4);
            }
            return false;
            break;

        case CK_UNLK:
            if (record->event.pressed)
            {
                layer_off(_BL1);
                layer_off(_BL2);
                layer_off(_FL3);
                layer_off(_FL4);
            }
            return false;
            break;

        case CK_LL3:
            if (record->event.pressed)
            {
                layer_on(_FL3);
                layer_off(_FL4);
            }
            return false;
            break;

        case CK_LL4:
            if (record->event.pressed)
            {
                layer_on(_FL4);
                layer_off(_FL3);
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

        default:
            break;

    }
    return true;
};

// Combo to access to boot (w/o erasing memory)
const uint16_t PROGMEM combos[] = {KC_Q, KC_P, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(combos, QK_BOOT),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // slow tapping for weak fingers
        case MT(MOD_LSFT, KC_A):
        case MT(MOD_RSFT, KC_SCLN):
        case MT(MOD_LALT, KC_D): // osamu special
        case MT(MOD_LALT, KC_U): // osamu special
        case MT(MOD_LSFT, KC_1):
        case MT(MOD_RSFT, KC_0):
        case MT(MOD_LALT, KC_3): // osamu special
            return TAPPING_TERM * 2;
        // thumbs are fast
        case LT(_FL1, KC_SPC):
        case LT(_FL2, KC_SPC):
            return TAPPING_TERM * 3 / 4;
        default:
            return TAPPING_TERM;
    }
};

