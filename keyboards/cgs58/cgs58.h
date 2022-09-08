// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=78 sts=4 ts=24 sw=4 et ai:

#pragma once

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments in physical positions
// The second converts the arguments into a two-dimensional sensing array positions
#define XXX KC_NO
#define LAYOUT( \
        k00, k01, k02, k03, k04, k05, k06,           k09, k0a, k0b, k0c, k0d, k0e, k0f, \
        k10, k11, k12, k13, k14, k15, k16,           k19, k1a, k1b, k1c, k1d, k1e, k1f, \
        k20, k21, k22, k23, k24, k25, k26,           k29, k2a, k2b, k2c, k2d, k2e, k2f, \
        k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f  \
        ) \
{ \
      { k00, k01, k02, k03, k04, k05, k06, XXX },\
      { k10, k11, k12, k13, k14, k15, k16, XXX },\
      { k20, k21, k22, k23, k24, k25, k26, XXX },\
      { k30, k31, k32, k33, k34, k35, k36, k37 },\
      { XXX, k09, k0a, k0b, k0c, k0d, k0e, k0f },\
      { XXX, k19, k1a, k1b, k1c, k1d, k1e, k1f },\
      { XXX, k29, k2a, k2b, k2c, k2d, k2e, k2f },\
      { k38, k39, k3a, k3b, k3c, k3d, k3e, k3f } \
}


#define fn_led_of(x) writePinHigh(x)
#define fn_led_on(x) writePinLow(x)
