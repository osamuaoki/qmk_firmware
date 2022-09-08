# MCU name
MCU = STM32F411

BOARD = BLACKPILL_STM32_F411

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

SPLIT_KEYBOARD = yes
# split settings https://github.com/qmk/qmk_firmware/blob/master/docs/serial_driver.md
SERIAL_DRIVER = usart

VIA_ENABLE = no
# customized for osamu-keymap
MIDI_ENABLE = no
DYNAMIC_MACRO_ENABLE = no
##AUTO_SHIFT_ENABLE = yes
COMBO_ENABLE = no


