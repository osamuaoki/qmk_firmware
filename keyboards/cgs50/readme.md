# cgs50

![cgs50](imgur.com image replace me!)

*Cartesian Grid Split 50 Keyboard*

* Keyboard Maintainer: [Osamu Aoki <osamu@debian.org>](https://github.com/osamuaoki)
* Hardware Supported: blackpill
* Hardware Availability: https://github.com/osamuaoki/cg56 (TBD) https://osamuaoki.github.io/jp/2022/09/01/blackpill-4/

Make example for this keyboard (after setting up your build environment):

    make cgs50:default

Flashing example for this keyboard:

    make cgs50:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB -- for cgs50, there are 2 buttons involved.
  * Push `BOOT0` --> Push `RESET` --> Release `RESET` --> Release `BOOT0`.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available -- for cgs50, combo of Q-P

## Reference

 * qmk_firmware/keyboards/handwired/dactyl_manuform/6x6
