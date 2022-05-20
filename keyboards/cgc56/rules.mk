# MCU name
MCU = at90usb1286

# Bootloader selection
BOOTLOADER = qmk-hid

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = yes          # Audio output

# customized for osamu-keymap
MIDI_ENABLE = no
DYNAMIC_MACRO_ENABLE = no
##AUTO_SHIFT_ENABLE = yes
COMBO_ENABLE = yes

