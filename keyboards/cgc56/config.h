// Copyright 2022 Osamu Aoki <osamu@debian.org> (@osamuaoki)
// SPDX-License-Identifier: GPL-2.0-or-later
// vim:se tw=78 sts=4 ts=24 sw=4 et ai:

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
//#define VENDOR_ID    0xFEED
//#define PRODUCT_ID   0x0000
//#define DEVICE_VER   0x0001
//#define MANUFACTURER "osamuaoki"
//#define PRODUCT      "cgc56"

/* key matrix size */
//#define MATRIX_ROWS 8
//#define MATRIX_COLS 7

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
//#define MATRIX_ROW_PINS { B7, D0, D1, D2, D3, D4, D5, D7 }
//#define MATRIX_COL_PINS { E0, E1, C0, C1, C2, C3, C4 }
//#define UNUSED_PINS

/* COL2ROW, ROW2COL */
//#define DIODE_DIRECTION COL2ROW
// COL2ROW: COL=INPUT(pull-upped) ROW=OUTPUT(normally high)

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
// NOT APPLICABLE so comment out to be clear
// #define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

// ////////////////////////////////////////////////////////////////
// LED for POWER, RAISE, LOWER, ... (turn on only 4 or less)
//   LED[1:4][R:B] = { B6,  B5,  F6,  F7,  F4,  F5,  C7,  C5}
//                     Q/R  Q/B  T/R  T/B  Y/R  Y/B  P/R  P/B
//                     (Don't enable JTAG if F5-F7 is used)
#define LED_Q_RED_PIN B6
#define LED_Q_BLU_PIN B5
#define LED_T_RED_PIN F6
#define LED_T_BLU_PIN F7
#define LED_Y_RED_PIN F4
#define LED_Y_BLU_PIN F5
#define LED_P_RED_PIN C7
#define LED_P_BLU_PIN C5
//   INTERNAL LED       = { D6 }
// ////////////////////////////////////////////////////////////////
//
// sort-of #define LED_CAPS_LOCK_PIN LED_Q_RED_PIN
#define LED_CAPS_LOCK_PIN F6
// sort-of #define LED_NUM_LOCK_PIN LED_T_RED_PIN
#define LED_NUM_LOCK_PIN F4
// sort-of #define LED_SCROLL_LOCK_PIN LED_Y_RED_PIN
//#define LED_SCROLL_LOCK_PIN F4
// unix kb
//#define LED_COMPOSE_PIN F4
// japanese kb
//#define LED_KANA_PIN F4

// taken from planck
//   Sound[0] = { C6 } (OCR3A, Timer 3, channel A, 16 bits)
#define QMK_SPEAKER C6
#define AUDIO_VOICES
#define AUDIO_PIN C6
#define AUDIO_CLICKY

//#define BACKLIGHT_PIN B5
//#define BACKLIGHT_LEVELS 3
//#define BACKLIGHT_BREATHING

//#define RGB_DI_PIN E2
//#ifdef RGB_DI_PIN
//#    define RGBLED_NUM 16
//#    define RGBLIGHT_HUE_STEP 8
//#    define RGBLIGHT_SAT_STEP 8
//#    define RGBLIGHT_VAL_STEP 8
//#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
//#    define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
//#    define RGBLIGHT_ANIMATIONS
/*== or choose animations ==*/
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
//#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
/*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//#    define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
/*==== use exp() and sin() ====*/
//#    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//#    define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
//#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
//#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
//#define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
//#define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* tap term per key */
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

/* Select MOD TAP to behave like default LAYER TAP (non-default) */
/* This is needed for home position mod keymaps */
#define IGNORE_MOD_TAP_INTERRUPT
/* Both LAYER TAP and MOD TAP can be rolling-pressed within TAPPING_TERM */
/* This is optional to accommodate the fast typer */
/* This is enabled by default if TAPPING_TERM >= 500 */
#define PERMISSIVE_HOLD

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

// auto shift
//#define AUTO_SHIFT_TIMEOUT 150
//#define NO_AUTO_SHIFT_NUMERIC
//#define NO_AUTO_SHIFT_SPECIAL

// no reentering
#define DYNAMIC_MACRO_NO_NESTING

// COMBO P+Q for QK_BOOT etc.
#define COMBO_COUNT 3

#define DEBUG_ACTION

// Delay between pressing a movement key and cursor movement
//#define MOUSEKEY_DELAY                        10
#define MOUSEKEY_DELAY	                        10
// Time between cursor movements in milliseconds
//#define MOUSEKEY_INTERVAL	20
#define MOUSEKEY_INTERVAL	5
// Step size
//#define MOUSEKEY_MOVE_DELTA	8
#define MOUSEKEY_MOVE_DELTA	1
// Maximum cursor speed at which acceleration stops
//#define MOUSEKEY_TIME_TO_MAX	30
#define MOUSEKEY_TIME_TO_MAX	100
// Time until maximum cursor speed is reached
#define MOUSEKEY_MAX_SPEED	10
// Delay between pressing a wheel key and wheel movement
#define MOUSEKEY_WHEEL_DELAY	10
// Time between wheel movements
#define MOUSEKEY_WHEEL_INTERVAL	80
// Maximum number of scroll steps per scroll action
#define MOUSEKEY_WHEEL_MAX_SPEED	8
// Time until maximum scroll speed is reached
#define MOUSEKEY_WHEEL_TIME_TO_MAX              40

#define KEYMAP_CONFIG_RAM
