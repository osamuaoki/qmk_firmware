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
//#define PRODUCT      "cgs50"

/* key matrix size */
#define MATRIX_ROWS 8  // Rows are doubled-up
#define MATRIX_COLS 7

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

// A9-A12 can't be used (USB conflict) for I/O
#define MATRIX_ROW_PINS { B12, B13, B14, B15 }
#define MATRIX_COL_PINS { B8, B3, A15, B9, B4, B5, C14 }

#define MATRIX_ROW_PINS_RIGHT { B12, B13, B14, B15 }
#define MATRIX_COL_PINS_RIGHT { A6, A3, A2, A1, A4, A5, C15 }
//#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW
// COL2ROW: COL=INPUT(pull-upped) ROW=OUTPUT(normally high)

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
// NOT APPLICABLE so comment out to be clear
// #define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

//   INTERNAL LED       = { C13 }
// ////////////////////////////////////////////////////////////////
//
// sort-of #define LED_CAPS_LOCK_PIN LED_Q_RED_PIN
//#define LED_CAPS_LOCK_PIN B6
// sort-of #define LED_NUM_LOCK_PIN LED_T_RED_PIN
//#define LED_NUM_LOCK_PIN F6
// sort-of #define LED_SCROLL_LOCK_PIN LED_Y_RED_PIN
//#define LED_SCROLL_LOCK_PIN F4
// unix kb
//#define LED_COMPOSE_PIN F4
// japanese kb
//#define LED_KANA_PIN F4
//
//Blackpill onboard blue LED
#define LED_BLUE C13

// taken from planck
//   Sound[0] = { C6 } (OCR3A, Timer 3, channel A, 16 bits)
//#define QMK_SPEAKER C6
//#define AUDIO_VOICES
//#define AUDIO_PIN C6
//#define AUDIO_CLICKY

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
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

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

/* enable retro tapping */
//#define RETRO_TAPPING

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
// right top row = 4
#define BOOTMAGIC_LITE_ROW_RIGHT    4
// right most column = 15
#define BOOTMAGIC_LITE_COLUMN_RIGHT 6

// auto shift
//#define AUTO_SHIFT_TIMEOUT 150
//#define NO_AUTO_SHIFT_NUMERIC
//#define NO_AUTO_SHIFT_SPECIAL

// no reentering
//#define DYNAMIC_MACRO_NO_NESTING

// COMBO P+Q for QK_BOOT etc.
#define COMBO_COUNT 3
/////////////////////////////////////////////////////////////////////////////////////////////////

// in col2row col is input, and row is output
// #define SPLIT_HAND_MATRIX_GRID A10, A4
//
// Ground B10 with 10kohm to grand indicate it is left side
#define SPLIT_HAND_PIN              B10
#define SPLIT_HAND_PIN_LOW_IS_LEFT

/* connection */
// https://github.com/qmk/qmk_firmware/blob/master/docs/serial_driver.md#choosing-a-driver-subsystem
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SOFT_SERIAL_PIN B6     // USART TX pin
#define SERIAL_USART_RX_PIN B7     // USART RX pin
#define SERIAL_USART_TX_PIN SOFT_SERIAL_PIN     // USART TX pin

#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: 460800 baud (experimental only)
                                   //  1: 230400 baud (default)
                                   //  2: 115200 baud
                                   //  3: 57600 baud
                                   //  4: 38400 baud
                                   //  5: 19200 baud
#define SERIAL_USART_DRIVER SD1    // USART driver of 
                                   //
                                   // TX and RX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 20    // USART driver timeout. default 20

// Communication Options
//  -- taken from https://github.com/qmk/qmk_firmware/blob/master/docs/feature_split_keyboard.md

#define FORCED_SYNC_THROTTLE_MS 100
// This sets the maximum number of milliseconds before forcing a
// synchronization of data from master to slave. Under normal circumstances
// this sync occurs whenever the data changes, for safety a data transfer
// occurs after this number of milliseconds if no change has been detected
// since the last sync.

#define SPLIT_MAX_CONNECTION_ERRORS 10
// This sets the maximum number of failed communication attempts (one per scan
// cycle) from the master part before it assumes that no slave part is
// connected. This makes it possible to use a master part without the slave
// part connected.
//
// Set to 0 to disable the disconnection check altogether.

#define SPLIT_CONNECTION_CHECK_TIMEOUT 500
// How long (in milliseconds) the master part should block all connection
// attempts to the slave after the communication has been flagged as
// disconnected (see SPLIT_MAX_CONNECTION_ERRORS above).
//
// One communication attempt will be allowed everytime this amount of time has
// passed since the last attempt. If that attempt succeeds, the communication
// is seen as working again.
//
// Set to 0 to disable this throttling of communications while disconnected.
// This can save you a couple of bytes of firmware size.
//
// Data Sync Options The following sync options add overhead to the split
// communication protocol and may negatively impact the matrix scan speed when
// enabled. These can be enabled by adding the chosen option(s) to your
// config.h file.

#define SPLIT_TRANSPORT_MIRROR
// This mirrors the master side matrix to the slave side for features that
// react or require knowledge of master side key presses on the slave side.
// The purpose of this feature is to support cosmetic use of key events (e.g.
// RGB reacting to keypresses).

#define SPLIT_LAYER_STATE_ENABLE
// This enables syncing of the layer state between both halves of the split
// keyboard. The main purpose of this feature is to enable support for use of
// things like OLED display of the currently active layer.

#define SPLIT_LED_STATE_ENABLE
// This enables syncing of the Host LED status (caps lock, num lock, etc)
// between both halves of the split keyboard. The main purpose of this feature
// is to enable support for use of things like OLED display of the Host LED
// status.

//#define SPLIT_MODS_ENABLE
// This enables transmitting modifier state (normal, weak and oneshot) to the
// non primary side of the split keyboard. The purpose of this feature is to
// support cosmetic use of modifer state (e.g. displaying status on an OLED
// screen).

//#define SPLIT_WPM_ENABLE
// This enables transmitting the current WPM to the slave side of the split
// keyboard. The purpose of this feature is to support cosmetic use of WPM
// (e.g. displaying the current value on an OLED screen).

//#define SPLIT_OLED_ENABLE
// This enables transmitting the current OLED on/off status to the slave side
// of the split keyboard. The purpose of this feature is to support state
// (on/off state only) syncing.

// #define SPLIT_ST7565_ENABLE
// This enables transmitting the current ST7565 on/off status to the slave
// side of the split keyboard. The purpose of this feature is to support state
// (on/off state only) syncing.

// #define SPLIT_POINTING_ENABLE
// This enables transmitting the pointing device status to the master side of
// the split keyboard. The purpose of this feature is to enable use pointing
// devices on the slave side.

