// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=78 sts=4 ts=24 sw=4 et ai:
#include "cgs58.h"

// This is to turn on blue LED on blackpill upon power up.
void keyboard_pre_init_kb(void) {
    setPinOutput(LED_BLUE);
    keyboard_pre_init_user();
}

