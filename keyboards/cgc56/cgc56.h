// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=78 sts=4 ts=24 sw=4 et ai:

#pragma once

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments in physical positions
// The second converts the arguments into a two-dimensional sensing array positions
#define LAYOUT( \
        k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, \
        k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, \
        k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, \
        k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d  \
        ) \
{ \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25, k26 }, \
    { k30, k31, k32, k33, k34, k35, k36 }, \
    { k07, k08, k09, k0a, k0b, k0c, k0d }, \
    { k17, k18, k19, k1a, k1b, k1c, k1d }, \
    { k27, k28, k29, k2a, k2b, k2c, k2d }, \
    { k37, k38, k39, k3a, k3b, k3c, k3d }  \
}

#define fn_led_on(x) writePinHigh(x)
#define fn_led_of(x) writePinLow(x)
