// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=78 sts=4 ts=24 sw=4 et ai:
#include "cgc56.h"
#include "wait.h"

// There is a limit for total DC current of IC to be 200 mA. (or 100mA for
// each port group, 40mA for each PIN).
//
// I have 4 of 2-color LEDs with each limiting to 18mA, turning all of them
// cause to consume 144 mA.

// Flash LEDs as KB starts
void keyboard_pre_init_kb(void) {
    setPinOutput(LED_Q_RED_PIN);
    setPinOutput(LED_Q_BLU_PIN);
    setPinOutput(LED_T_RED_PIN);
    setPinOutput(LED_T_BLU_PIN);
    setPinOutput(LED_Y_RED_PIN);
    setPinOutput(LED_Y_BLU_PIN);
    setPinOutput(LED_P_RED_PIN);
    setPinOutput(LED_P_BLU_PIN);
    fn_led_on(LED_Q_RED_PIN);
    fn_led_on(LED_T_RED_PIN);
    fn_led_on(LED_Y_RED_PIN);
    fn_led_on(LED_P_RED_PIN);
    wait_ms(100);
    fn_led_of(LED_Q_RED_PIN);
    fn_led_of(LED_T_RED_PIN);
    fn_led_of(LED_Y_RED_PIN);
    fn_led_of(LED_P_RED_PIN);
    fn_led_on(LED_Q_BLU_PIN);
    fn_led_on(LED_T_BLU_PIN);
    fn_led_on(LED_Y_BLU_PIN);
    fn_led_on(LED_P_BLU_PIN);
    wait_ms(100);
    fn_led_on(LED_Q_RED_PIN);
    fn_led_on(LED_T_RED_PIN);
    fn_led_on(LED_Y_RED_PIN);
    fn_led_on(LED_P_RED_PIN);
    fn_led_of(LED_Q_BLU_PIN);
    fn_led_of(LED_T_BLU_PIN);
    fn_led_of(LED_Y_BLU_PIN);
    fn_led_of(LED_P_BLU_PIN);
    wait_ms(100);
    keyboard_pre_init_user();
}

