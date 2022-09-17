// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=128 sts=4 ts=24 sw=4 et ai:
#include QMK_KEYBOARD_H

// This is a programmable keyboard with 6 layers:
// * 1 default layer (_BL1)
// * 2 temporary layers (_FL1, _FL2)
// * 2 lockable  layers (_FL3, _FL4)
//     * Access via: CK_LL3, CK_LL4, CK_UNLK
// * LEDs are lit according to the effective layer
//
enum layer_names {
    _BL1, // QWERTY base
    _FL1, // Layer: F1-F12  1-0, symbols         -- transient
    _FL2, // cursor                              -- lockable and transient
    _FL3, // numpad                              -- lockable
    _FL4, // mouse  (internal, macro)            -- lockable
};

// All custom keycodes are after SAFE_RANGE
enum custom_keycodes {
    // lock-layers
    CK_LL2 = SAFE_RANGE,
    CK_LL3,
    CK_LL4,
    // unlock lock-layers
    CK_UNLK,
    // mouse
    CK_M_UL,
    CK_M_UR,
    CK_M_DL,
    CK_M_DR,
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
// left side one hand moves (ZZ, ^A, ^Z, ^X, ^C, ^V, ^B)
#define LC_ESC MT(MOD_LCTL, KC_ESC)
#define LS_MUTE MT(MOD_LSFT, KC_MUTE)

// Momentarily Layer, Layer-Tap for thumb/index keys and its support
#define K1_SPC LT(_FL1, KC_SPC)
#define K2_V   LT(_FL2, KC_V)
#define LG_C MT(MOD_LGUI, KC_C)

// Odd keys and effects under US/JP/ISO
//      KEYCODE HEX     us      US      iso     ISO     jis     JIS     かな
//      KC_NUHS  32     \       |       #       ~       ]       }
//      KC_NUBS  64     <       >       \       |
//      KC_INT1  87                                     \       _       ろ
//      KC_INT2  88                                     HIRAGANA/KATAKANA
//      KC_INT3  89     \       |                       \       |       ー
//      KC_INT4  8A                                     変換
//      KC_INT5  8B                                     無変換
//

// mc: ALT-P/ALT-N/ALT-ENT/CTL-U/CTL-R
#define KC_ALTP LALT(KC_P)
#define KC_ALTN LALT(KC_N)
#define KC_CTLU LCTL(KC_U)
#define KC_CTLR LCTL(KC_R)

// TRANS (pressed)
#define vvvvvvv KC_TRNS

// This 12x3_4 (40) is meant to be the most finger friendly keymap using
// part of 4x14 ortholinear keyboard
//
// This keymap offers a minimum stress with easy transition among:
//   - the generic keyboard with long space bar
//   - the corne-like (3row * 6column + 3thumb) x2 split keyboard
//   - the planck-like 4x12 ortholinear keyboard
//   - the let's-split-like (4row * 6column) x2 split keyboard
//
//  This is ANSI focused with care to support JIS.
//  The ISO support is the last priority.
//  AudioMute and PrintScreen keys are given high priority
//

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ****************************************************************************************************************************************
     * Baseline -- for normal typing
     *     KC_INT4 and KC_INT5 are for the JIS user
     * ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
     * │Tab│ Q │ W │ E │ R │ T │               │ Y │ U │ I │ O │ P │BS │
     * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
     * │Esc│ A │ S │ D │ F │ G │               │ H │ J │ K │ L │ ; │Ent│
     * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
     * │Mut│ Z │ X │ C │ V │ B │               │ N │ M │ , │ . │ / │Psc│
     * ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │MUH│Sp1│   │       │   │Sp1│HEN│   │   │   │   │
     * └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
     */
    [_BL1] = LAYOUT(
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            LC_ESC,  LS_A,    LC_S,    LA_D,    LG_F,    RA_G,                      RA_H,    LG_J,    LA_K,    RC_L,    RS_SCLN, KC_ENT,
            LS_MUTE, KC_Z,    KC_X,    LG_C,    K2_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_PSCR,
            KC_LCTL, KC_LGUI, KC_LSFT, KC_LALT, KC_INT5, K1_SPC,  KC_INS,  KC_DEL,  K1_SPC,  KC_INT4, KC_RALT, KC_RSFT, KC_RGUI, KC_RCTL
            ),

    /* ****************************************************************************************************************************************
     * _FL1
     *     High Function keys F1-F10, F11, F12
     *     MidH Normal number keys
     *     MidL Odd symbol keys
     *     KC_INT1, KC_INT2, and KC_INT3 are for the JIS user
     *     KC_NUBS and KC_NUHS are for the ISO user
     * ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
     * │F11│F1 │F2 │F3 │F4 │F5 │               │F6 │F7 │F8 │F9 │F10│F12│
     * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
     * │Cap│ 1 │ 2 │ 3 │ 4 │ 5 │               │ 6 │ 7 │ 8 │ 9 │ 0 │App│
     * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
     * │NUB│ ` │NUH│ー │ - │ = │               │ [ │ ] │ \ │ろ │ ' │LL2│
     * ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │vvv│   │       │   │vvv│KAN│   │   │   │   │
     * └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
     */
    [_FL1] = LAYOUT(
            KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
            KC_CAPS, LS_1,    LC_2,    LA_3,    LG_4,    RA_5,                      RA_6,    LG_7,    LA_8,    RC_9,    RS_0,    KC_APP,
            KC_NUBS, KC_GRV,  KC_NUHS, KC_INT3, KC_MINS, KC_EQL,                    KC_LBRC, KC_RBRC, KC_BSLS, KC_INT1, KC_QUOT, CK_LL2,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, vvvvvvv, XXXXXXX, XXXXXXX, vvvvvvv, KC_INT2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
            ),

    /* ****************************************************************************************************************************************
     * _FL2
     * Cursor
     * ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │App│   │               │Ins│PgU│Up │PgD│Del│LL4│
     * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
     * │   │Sft│Ctl│Alt│Gui│   │               │Hom│Lft│Dow│Rgt│End│LL3│
     * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │Gui│vvv│   │               │cU │aP │Tab│aN │cR │LL2│
     * ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │Spc│   │       │   │Spc│   │   │   │   │   │
     * └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
     */
    [_FL2] = LAYOUT(
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_APP,  XXXXXXX,                   KC_INS,  KC_PGUP, KC_UP,   KC_PGDN, KC_DEL,  CK_LL4,
            XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,                   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  CK_LL3,
            XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, vvvvvvv, XXXXXXX,                   KC_CTLU, KC_ALTP, KC_TAB,  KC_ALTN, KC_CTLR, CK_UNLK,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CK_UNLK, XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
            ),

    /* ****************************************************************************************************************************************
     * Numpad (locked layer)
     * ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
     * │   │   │   │Psc│ScL│Pau│               │Num│ 7 │ 8 │ 9 │ * │BS │
     * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
     * │   │Sft│Ctl│Alt│Gui│   │               │ / │ 4 │ 5 │ 6 │ + │PEn│
     * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │UNL│   │               │ 0 │ 1 │ 2 │ 3 │ - │Cal│
     * ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │UNL│   │       │   │ . │   │   │   │   │   │
     * └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
     * All off-main area (numpad etc.)
     */
    [_FL3] = LAYOUT(
            XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SCRL, KC_PAUS,                  KC_NUM,  KC_KP_7, KC_KP_8, KC_KP_9, KC_PAST, KC_BSPC,
            XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,                  KC_PSLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_PENT,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CK_UNLK, XXXXXXX,                  KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_PMNS, KC_CALC,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CK_UNLK,XXXXXXX, XXXXXXX, KC_PDOT, XXXXXXX, CK_UNLK, CK_UNLK, XXXXXXX, XXXXXXX
            ),

    /* ****************************************************************************************************************************************
     * Internal and mouse locked layer: mouse keys are mostly useless
     */
    [_FL4] = LAYOUT(
            XXXXXXX, EC_SWAP, CK_ON,   NK_ON,   KC_APP,  KC_VOLU,                   KC_BTN3, CK_M_UL, KC_MS_U, CK_M_UR, KC_WH_U, KC_ACL0,
            XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_MUTE,                   KC_WH_L, KC_MS_L, KC_BTN1, KC_MS_R, KC_WH_R, KC_ACL1,
            XXXXXXX, EC_NORM, CK_OFF,  NK_OFF,  CK_UNLK, KC_VOLD,                   KC_BTN2, CK_M_DL, KC_MS_D, CK_M_DR, KC_WH_D, KC_ACL2,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CK_UNLK, XXXXXXX, XXXXXXX, KC_BTN1, XXXXXXX, CK_UNLK, CK_UNLK, XXXXXXX, XXXXXXX
            ),

};

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

void fn_led(pin_t pin, bool flag) {
    if (flag) {
        writePinLow(pin); // ON
    } else {
        writePinHigh(pin); // OFF
    }
}

// blink (ms) 
#define BLINK_ON  1000
#define BLINK_OFF 500
#include "sync_timer.h"

// Continuous LED on/off indicates highest active layer for every matrix scan
void matrix_scan_user(void) {
    static uint16_t key_timer = 0;
    bool flag;
    if (timer_elapsed(key_timer) < BLINK_ON)
    {
        flag = true;
    } else if (timer_elapsed(key_timer) < ( BLINK_ON + BLINK_OFF) )
    {
        flag = false;
    } else {
        key_timer = timer_read();
        flag = true;
    }
    // check from MSB -> LSB
    if (layer_state & (1L << _FL4))
    {   // mouse
        fn_led(LED_BLUE, flag);

    } else if (layer_state & (1L << _FL3))
    {   // numpad
        if (is_keyboard_left())
        {
            fn_led(LED_BLUE, true);
        } else {
            fn_led(LED_BLUE, flag);
        }

    } else if (layer_state & (1L << _FL2))
    {
        if (is_keyboard_left())
        {
            fn_led(LED_BLUE, true);
        } else {
            fn_led(LED_BLUE, false);
        }

    } else if (layer_state & (1L << _FL1))
    {
        if (is_keyboard_left())
        {
            fn_led(LED_BLUE, false);
        } else {
            fn_led(LED_BLUE, true);
        }
    } else // No-Fn pressed
    {
        fn_led(LED_BLUE, true);
    }
}

// Continuous LED on/off indicates highest active layer for every slave matrix scan
void matrix_slave_scan_user(void) {
    matrix_scan_user();
}

// define macro actions for mouse keys
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch(keycode)
    {
        case CK_UNLK:
            if (record->event.pressed)
            {
                layer_off(_FL2);
                layer_off(_FL3);
                layer_off(_FL4);
            }
            return false;

        case CK_LL2:
            if (record->event.pressed)
            {
                layer_on(_FL2);
                layer_off(_FL3);
                layer_off(_FL4);
            }
            return false;

        case CK_LL3:
            if (record->event.pressed)
            {
                layer_off(_FL2);
                layer_on(_FL3);
                layer_off(_FL4);
            }
            return false;

        case CK_LL4:
            if (record->event.pressed)
            {
                layer_off(_FL2);
                layer_on(_FL4);
                layer_off(_FL3);
            }
            return false;

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

        default:
            return true;

    }
};

// Combo to access to boot (w/o erasing memory)
const uint16_t PROGMEM combos_boot[] = {KC_Q, KC_P, COMBO_END};
const uint16_t PROGMEM combos_clr[] = {KC_TAB, KC_BSPC, COMBO_END};
const uint16_t PROGMEM combos_dbg[] = {KC_TAB, KC_ENT, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(combos_boot, QK_BOOT),
    COMBO(combos_clr, EE_CLR),
    COMBO(combos_dbg, DB_TOGG),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // slow MT for weak fingers
        case MT(MOD_LSFT, KC_A):
        case MT(MOD_RSFT, KC_SCLN):
        case MT(MOD_LSFT, KC_1):
        case MT(MOD_RSFT, KC_0):
        case MT(MOD_LSFT, KC_ESC):
        case MT(MOD_LCTL, KC_MUTE):
        case MT(MOD_LALT, KC_D): // osamu special
        case MT(MOD_LALT, KC_3): // osamu special
            return TAPPING_TERM * 2;
        // LT are fast
        case LT(_FL1, KC_SPC):
        case LT(_FL2, KC_V):
            return TAPPING_TERM * 3 / 4;
        // MT are normal
        default:
            return TAPPING_TERM;
    }
};

