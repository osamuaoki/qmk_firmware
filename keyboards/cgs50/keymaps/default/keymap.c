// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=78 sts=4 ts=24 sw=4 et ai:
#include QMK_KEYBOARD_H

// For a more practical keymap example, see "osamu"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* ****************************************************************************************************************************************
     * Baseline
     * ┌───┬───┬───┬───┬───┬───┐               ┌───┬───┬───┬───┬───┬───┐
     * │Tab│ Q │ W │ E │ R │ T │               │ Y │ U │ I │ O │ P │BS │
     * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
     * │Esc│ A │ S │ D │ F │ G │               │ H │ J │ K │ L │ ; │Ent│
     * ├───┼───┼───┼───┼───┼───┤               ├───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │               │ N │ M │ , │ . │ / │Sft│
     * ├───┼───┼───┼───┼───┼───┼───┐       ┌───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│Gui│Alt│ 1 │ 2 │Spc│ 5 │       │ 6 │Spc│ 3 │ 4 │ 5 │ 6 │Ctl│
     * └───┴───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┴───┘
     */
    [0] = LAYOUT(
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_LCTL, KC_LGUI, KC_LALT, KC_1,    KC_2,    KC_SPC,  KC_5,    KC_6,    KC_SPC,  KC_3,    KC_4,    KC_5,    KC_6,    KC_RCTL
            ),
};


