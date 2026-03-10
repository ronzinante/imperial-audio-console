# imperial audio console

See related repo: <https://github.com/ronzinante/insertfinity>

## Build (Mk2)

- Raspberry Pi Pico microcontroller
- 0.96" OLED display
- MP3 audio playback via MAX98357A
- 3W Dayton audio exciter
- Control button reminiscent of Death Star consoles
- Star Wars inspired design, interface and alerts

## Iterations history

### Mk2 (latest)

Video: <https://www.youtube.com/@iwantcolorsback>

Code: [mk2](mk/mk2/)

![mk2-overview](img/mk2-overview.jpeg)
*Overview*
![mk2-map](img/mk2-map.jpeg)
*Map*
![mk2-selection](img/mk2-selection.jpeg)
*Selection mode activated*
![mk2-internal](img/mk2-internal.jpeg)
*Internal*

Design wins and features:

- Design was improved to resemble Star Wars universe.
- The exciter is now externally mounted and can be attached to a suitable resonant surface oriented toward the listener.
- Illuminated pushbutton with **Galactic Empire emblem**. The pushbutton style evoke the Death Star control console (ISI/Grass Valley Switcher).
- Selection mode with single pushbutton.
- Dynamic 0.96" display. **U8G2** is used for the display.
- Raspberry Pi Pico built in LED is exposed externally using 1.75mm transparent PLA filament.
- LittleFS
- Arduino-pico
  
Design fails:

- Almost no storage for additional song. Only Raspberry Pi Pico was used for storage.
- No access to BOOTSEL button.
- Requires USB connection for power
- OLED display animation stops during audio reproduction (only 1 core used).

#### Bill of materials Mk2

| Link | Description | Quantity | Manufacturer |
| ------ | ------------- | ---------------- | ---------------- |
| [mk2](https://github.com/ronzinante/insertfinity/tree/main/stl/insert/insert-pedestal-star-wars-mk2) | STL part for 3D printing | - | - |
| - | Raspberry Pi Pico | 1 | Raspberry |
| - | Amplifier MAX98357A | 1 | - |
| - | DAEX13CT-4 Coin Type 13mm Exciter 3W 4 Ohm | 1 | Dayton Audio |
| - | Illuminated pushbutton PB26-13M | 1 | Honyone |
| - | Oled 0,96" I2C | 1 | - |
| - | T1 3/4 LED clear red | 1 | - |
| - | 1.75mm transparent PLA filament | 1 | - |
| - | Straw | 1 | - |

*NOTE* The illuminated pushbutton was CNC-machined to house a 5 mm LED. See below:

![mk2-cnc](img/mk2-cnc.jpeg)
*CNC machining*

### Mk1 (archived)

Video: <https://www.youtube.com/@iwantcolorsback>

Code: [mk1](mk/mk1/)

![mk1](img/mk1.jpeg)
*External*

![mk1-internal](img/mk1-internal.jpeg)
*Internal*

![mk1-exciter](img/mk1-exciter.jpeg)
*Exciter and foam panel*

Design fails:

- Boring design. Only the upper part resembles Star Wars.
- Nonoptimal sound reproduction. Exciter is located and oriented improperly. The foam panel is not facing the listener but is facing downward.
- Complex audio management. Both Micropython and Circuitpython have limitations.
- Almost no storage for additional audio effects. Only Raspberry Pi Pico was used for storage.
- Assembly issue caused by poor design choice.
- Requires USB connection for power
- No access to BOOTSEL button.

#### Bill of materials Mk1

| Link | Description | Quantity | Manufacturer |
| ------ | ------------- | ---------------- | ---------------- |
| [mk1](https://github.com/ronzinante/insertfinity/tree/main/stl/insert/insert-pedestal-star-wars-mk1) | STL part for 3D printing | - | - |
| - | Raspberry Pi Pico | 1 | Raspberry |
| - | Amplifier MAX98357A | 1 | - |
| - | DAEX13CT-4 Coin Type 13mm Exciter 3W 4 Ohm | 1 | Dayton Audio |
| - | Illuminated pushbutton PB26-13M | 1 | Honyone |
| - | T1 3/4 LED clear red | 1 | - |
| - | 1.75mm transparent PLA filament | 1 | - |
| - | Straw | 1 | - |
