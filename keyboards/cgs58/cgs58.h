// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=78 sts=4 ts=24 sw=4 et ai:

#pragma once

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments in physical positions
// The second converts the arguments into a two-dimensional sensing array positions
#define LAYOUT( \
        k00, k01, k02, k03, k04, k05, k06, k07, \
        k10, k11, k12, k13, k14, k15, k16, k17, \
        k20, k21, k22, k23, k24, k25, k26, k27, \
        k30, k31, k32, k33, k34, k35, k36, k37  \
        ) \
{ \
      { k00, k01, k02, k03, k04, k05, k06 ,k07 },\
      { k10, k11, k12, k13, k14, k15, k16 ,k17 },\
      { k20, k21, k22, k23, k24, k25, k26 ,k27 },\
      { k30, k31, k32, k33, k34, k35, k36 ,k37 } \
}

#define fn_led_of(x) writePinHigh(x)
#define fn_led_on(x) writePinLow(x)
