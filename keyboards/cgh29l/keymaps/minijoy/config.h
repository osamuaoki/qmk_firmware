// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=78 sts=4 ts=24 sw=4 et ai:

#pragma once

// JOYSTICK
// Max 32
#define JOYSTICK_BUTTON_COUNT 3
// Max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXES_COUNT 2
// Web -- https://www.reddit.com/r/ErgoMechKeyboards/comments/r6btqm/qmk_joystick_with_stm32f411_blackpill/
// Tested -- https://gamepad-tester.com/
#define JOYSTICK_AXES_RESOLUTION 8
#define USB_POLLING_INTERVAL_MS 4

#include_next "config.h"
