// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=78 sts=4 ts=24 sw=4 et ai:
#include "cgh29l.h"

// This is to blink blue LED on blackpill upon power up.
void keyboard_pre_init_kb(void) {
    setPinOutput(LED_BLUE);
    fn_led_on(LED_BLUE);
    wait_ms(100);
    fn_led_of(LED_BLUE);
    wait_ms(100);
    fn_led_of(LED_BLUE);
    wait_ms(100);
    keyboard_pre_init_user();
}

