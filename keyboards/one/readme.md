# one

![one](imgur.com image replace me!)

ミュートスイッチ(mute switch)

D0 -> SWITCH (the other end of switch is grounded)
D3 -> RGB
F0 -> Anolog

* Keyboard Maintainer: [Osamu Aoki](https://github.com/osamuaoki)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make one:default

Flashing example for this keyboard:

    make one:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available


## Note on HW

スイッチマトリクスが普通の２次元のマトリクスで、スイッチの両方がMCUに繋がってる際：

* `COL --|<---___./.___ ROW(pull-up)` -- read
* `ROW --|<---___./.___ COL(pull up)` -- read

つまり：

* ダイオードのアノード側（矢印の根元）がMCU入力側
* カソード側（矢印の先端）がMCU出力側

スイッチマトリクスが１次元で、スイッチの一方がGNDに繋がってる際：
* `GND -------___./.___ ROW(pull-up)` -- read
* `GND -------___./.___ COL(pull up)` -- read

出力側は繋いでも良いが、１つなので選択状態と同じGNDに常に繋いでも同じ。

デフォルトの`#define DIODE_DIRECTION COL2ROW` のままだと、D0がCOLとなる。

