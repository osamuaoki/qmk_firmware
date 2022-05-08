// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=128 sts=4 ts=24 sw=4 et ai:
#include QMK_KEYBOARD_H
#include "wait.h"

// This is a programmable keyboard with 10 layers:
// * 1 default layer (_BL1)
// * 2 temporary top layers (_FL1, _FL2)
// * 2 locked top layers (_FL3, _FL4)
//     * Access via: CK_LL3, CK_LL4, CK_UNLK
// * LEDs are lit according to the effective layer
//
enum layer_names {
    _BL1, // QWERTY base
    _FL1, // Layer: F1-F10, 1-0, symbols
    _FL2, // Layer: F1-F10, 1-0, symbols (almost duplicate)
    _FL3, // numpad                                -- locked
    _FL4  // internal and mouse                    -- locked
};

// All custom keycodes are after SAFE_RANGE
enum custom_keycodes {
    // lock-layers
    CK_LL3 = SAFE_RANGE,
    CK_LL4,
    // unlock lock-layers
    CK_UNLK,
    // mouse
    CK_M_UL,
    CK_M_UR,
    CK_M_DL,
    CK_M_DR,
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
// side
#define LC_ESC MT(MOD_LCTL, KC_ESC)
#define LS_INS MT(MOD_LSFT, KC_INS)
#define RC_ENT MT(MOD_RCTL, KC_ENT)
#define RS_DEL MT(MOD_RSFT, KC_DEL)

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
//Uncomment one
//#define KBDTYPE_US
#define KBDTYPE_USJP
//#define KBDTYPE_USISO
//
#ifdef KBDTYPE_US
// US only keyboard
#define KC_XXX1 KC_PIPE
#define KC_XXX2 XXXXXXX
#define KC_XXX3 KC_UNDS
#define KC_XXX4 LCTL(KC_SPC)
#define KC_XXX5 LSFT(KC_SPC)
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
#define KC_XXX4 LCTL(KC_SPC)
#define KC_XXX5 LSFT(KC_SPC)
#endif

// For unlock caps ???
#define LS_CAPS LSFT(KC_CAPS)

// TRANS (pressed)
#define vvvvvvv KC_TRNS
// To be filled
#define KKKKKKK XXXXXXX
#define KC_XXXX XXXXXXX

// This is meant to be the most finger friendly keymap using
// part of 4x14 ortholinear keyboard
//
// This keymap offers a minimum stress with easy transition among:
//   - the standard TKL keyboard
//   - the corne-like (3row * 6column + 3thumb) x2 split keyboard
//   - the planck-like 4x12 ortholinear keyboard
//   - the let's-split-like (4row * 6column) x2 split keyboard

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ****************************************************************************************************************************************
     * QWERTY -- for normal typing
     *
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Tab│ Q │ W │ E │ R │ T │   │   │ Y │ U │ I │ O │ P │Bs │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Esc│ A │ S │ D │ F │ G │   │   │ H │ J │ K │ L │ ; │Ent│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ins│ Z │ X │ C │ V │ B │   │   │ N │ M │ , │ . │ / │Del│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │ ￪ │Sp1│ ￩ │ ￫ │Sp2│ ￬ │   │   │   │   │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_BL1] = LAYOUT(
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX, XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            LC_ESC,  LS_A,    LC_S,    LA_D,    LG_F,    RA_G,    XXXXXXX, XXXXXXX, RA_H,    LG_J,    LA_K,    RC_L,    RS_SCLN, RC_ENT,
            LS_INS,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RS_DEL,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   K1_SPC,  KC_LEFT, KC_RGHT, K2_SPC,  KC_DOWN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
            ),

    /* ****************************************************************************************************************************************
     * _FL1 (right side)
     * _FL2 (left side)
     *     High Function keys F1-F10 (F11, F12)
     *     MidH Normal number keys
     *     MidL Odd symbol keys
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │F11│F1 │F2 │F3 │F4 │F5 │   │   │F6 │F7 │F8 │F9 │F10│F12│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │EES│ 1 │ 2 │ 3 │ 4 │ 5 │   │   │ 6 │ 7 │ 8 │ 9 │ 0 │xx2│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Psc│Cap│ ~ │ー │ - │ = │   │   │ [ │ ] │ \ │ろ │ ' │LL3│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │PgU│xx5│Hom│End│xx4│PgD│   │   │   │   │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_FL1] = LAYOUT(
            KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
            CK_EENG, LS_1,    LC_2,    LA_3,    LG_4,    RA_5,    XXXXXXX, XXXXXXX, RA_6,    LG_7,    LA_8,    RC_9,    RS_0,    KC_XXX2,
            KC_PSCR, KC_CAPS, KC_GRV,  KC_XXX3, KC_MINS, KC_EQL,  XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, KC_XXX1, KC_QUOT, CK_LL3,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, vvvvvvv, KC_HOME, KC_END,  KC_XXX4, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
            ),
    [_FL2] = LAYOUT(
            KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX, XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
            CK_EENG, LS_1,    LC_2,    LA_3,    LG_4,    RA_5,    XXXXXXX, XXXXXXX, RA_6,    LG_7,    LA_8,    RC_9,    RS_0,    KC_XXX2,
            KC_PSCR, KC_CAPS, KC_GRV,  KC_XXX3, KC_MINS, KC_EQL,  XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, KC_XXX1, KC_QUOT, CK_LL4,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_XXX5, KC_HOME, KC_END,  vvvvvvv, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
            ),

    /* ****************************************************************************************************************************************
     * Numpad locked layer: Numpad/media
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Pau│Mut│Vup│Vdn│   │   │   │   │ - │ 7 │ 8 │ 9 │BS │Num│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Scr│Sft│Ctl│Alt│Gui│LL4│   │   │ * │ 4 │ 5 │ 6 │ + │Cal│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Psc│RE1│RE2│PL1│PL2│APP│   │   │ / │ 1 │ 2 │ 3 │PEn│ = │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │LL4│ULK│LL3│Ent│ . │ 0 │   │   │   │   │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     * All off-main area (numpad etc.)
     */
    [_FL3] = LAYOUT(
            KC_PAUS, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PMNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_BSPC, KC_NUM,
            KC_SCRL, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, CK_LL4,  XXXXXXX, XXXXXXX, KC_PAST, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_CALC,
            KC_PSCR, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, KC_APP,  XXXXXXX, XXXXXXX, KC_PSLS, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, KC_PEQL,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CK_LL4,  CK_UNLK, CK_LL3,  KC_ENT,  KC_PDOT, KC_KP_0, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
            ),

    /* ****************************************************************************************************************************************
     * Internal and muse locked layer: mouse keys (mostly useless)
     */
    [_FL4] = LAYOUT(
            XXXXXXX, CK_ON,   NK_ON,   XXXXXXX, DB_TOGG, EE_CLR,  XXXXXXX, XXXXXXX, KC_WH_U, CK_M_UL, KC_MS_U, CK_M_UR, KC_WH_U, KC_ACL0,
            EC_TOGG, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, CK_LL3,  XXXXXXX, XXXXXXX, KC_WH_L, KC_MS_L, KC_BTN1, KC_MS_R, KC_WH_R, KC_ACL1,
            KC_PSCR, CK_OFF,  NK_OFF,  XXXXXXX, XXXXXXX, KC_APP,  XXXXXXX, XXXXXXX, KC_WH_D, CK_M_DL, KC_MS_D, CK_M_DR, KC_WH_D, KC_ACL2,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CK_LL4,  CK_UNLK, CK_LL3,  KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
        fn_led_of(LED_Q_RED_PIN);
        wait_ms(50);
        fn_led_on(LED_P_RED_PIN);
        fn_led_on(LED_Q_RED_PIN);
        wait_ms(150);
    }
    fn_led_of(LED_P_RED_PIN);
    fn_led_of(LED_Q_RED_PIN);
    return;
}

void keyboard_post_init_user(void) {
  // Customize these values to desired behavior
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
  layer_on(_BL1);
  // normal setting
  set_single_persistent_default_layer(_BL1);
}

// Continuous LED on/off indicates highest active layer
// 4 BLUE LEDs and 1 RED LED used
// Other RED pins are for Caps/Scroll/Num Locks
layer_state_t layer_state_set_kb(layer_state_t orig_state) {
    layer_state_t state = layer_state_set_user(orig_state);
    // check from MSB -> LSB
    if (state & (1L << _FL4))
    {
        // B*___* R*..*
        fn_led_on(LED_Q_BLU_PIN);
        fn_led_of(LED_T_BLU_PIN);
        fn_led_of(LED_Y_BLU_PIN);
        fn_led_on(LED_P_BLU_PIN);
        fn_led_on(LED_Q_RED_PIN);
        fn_led_on(LED_P_RED_PIN);
    } else if (state & (1L << _FL3))
    {
        // B_**_ R*..*
        fn_led_of(LED_Q_BLU_PIN);
        fn_led_on(LED_T_BLU_PIN);
        fn_led_on(LED_Y_BLU_PIN);
        fn_led_of(LED_P_BLU_PIN);
        fn_led_on(LED_Q_RED_PIN);
        fn_led_on(LED_P_RED_PIN);
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
        // B**** R_.._
        fn_led_on(LED_Q_BLU_PIN);
        fn_led_on(LED_T_BLU_PIN);
        fn_led_on(LED_Y_BLU_PIN);
        fn_led_on(LED_P_BLU_PIN);
        fn_led_of(LED_Q_RED_PIN);
        fn_led_of(LED_P_RED_PIN);
    }
    return state ;
}

// define macro actions for mouse keys
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch(keycode)
    {
        case CK_UNLK:
            if (record->event.pressed)
            {
                fn_led_blinks(1);
                layer_off(_FL3);
                layer_off(_FL4);
            }
            return false;
            break;

        case CK_LL3:
            if (record->event.pressed)
            {
                fn_led_blinks(2);
                layer_on(_FL3);
                layer_off(_FL4);
            }
            return false;
            break;

        case CK_LL4:
            if (record->event.pressed)
            {
                fn_led_blinks(4);
                layer_on(_FL4);
                layer_off(_FL3);
            }
            return false;
            break;

        case CK_M_UL:
            if (record->event.pressed)
            {
                fn_led_blinks(3);
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
        case MT(MOD_LSFT, KC_1):
        case MT(MOD_RSFT, KC_0):
        case MT(MOD_LSFT, KC_ESC):
        case MT(MOD_LCTL, KC_INS):
        case MT(MOD_RSFT, KC_ENT):
        case MT(MOD_RCTL, KC_DEL):
        case MT(MOD_LALT, KC_D): // osamu special
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

