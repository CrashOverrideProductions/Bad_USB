# BadUSB Firmware <img align="right" src="https://github.com/CrashOverrideProductions/Tools/blob/main/Bad%20USB/images/logo.jpg?raw=true">

### Project: PlatformIO Migration of BadUSB Firmware (Malduino Elite Modified) <img alt="" align="right" src="https://img.shields.io/badge/Status-Code%20Review-informational?style=flat&logoColor=white&color=0EF9421" />

<img src="https://cdn.platformio.org/images/platformio-logo.17fdc3bc.png">

#### ChangeLog
```c++
09/12/2020  IMPORT MALDUINO ELITE SOURCE FROM SEYTONIC'S GITHUB REPOSITORY
09/12/2020  ADD HEADER & LICENCE DETAILS
09/12/2020  REMOVE DIP SWTICH | FILENAME = "Ducky.txt"
10/12/2020  REMOVE LED | ADD TEST PINOUT + TEST SUCCESSFUL
28/10/2020  ADD VID/PID HELPFUL INFO
18/04/2021  CAST 'buf' & 'repeatBuffer' (char*)malloc....
18/04/2021  MOVE 'runLine' FUNCTION BELOW 'runCommand' FUNCION - PLATFORMIO ISSUE
30/04/2021  IMPLEMENT 'NumLock', 'Pause/Break', 'Scroll-Lock', 'F13 - F23' KEYS

```

#### Platform IO Build Status
```c++
Processing leonardo (platform: atmelavr; board: leonardo; framework: arduino)
-----------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/atmelavr/leonardo.html
PLATFORM: Atmel AVR (3.3.0) > Arduino Leonardo
HARDWARE: ATMEGA32U4 16MHz, 2.50KB RAM, 28KB Flash
DEBUG: Current (simavr) On-board (simavr)
PACKAGES:
 - framework-arduino-avr 5.1.0
 - toolchain-atmelavr 1.70300.191015 (7.3.0)
LDF: Library Dependency Finder -> http://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 8 compatible libraries
Scanning dependencies...
Dependency Graph
|-- <Keyboard> 1.0.2
|   |-- <HID> 1.0
|-- <Mouse> 1.0.1
|   |-- <HID> 1.0
|-- <SD> 1.2.4
|   |-- <SPI> 1.0
Building in release mode
Compiling .pio\build\leonardo\src\main.cpp.o
Linking .pio\build\leonardo\firmware.elf
Checking size .pio\build\leonardo\firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [======    ]  62.2% (used 1593 bytes from 2560 bytes)
Flash: [=======   ]  68.8% (used 19722 bytes from 28672 bytes)
Building .pio\build\leonardo\firmware.hex
=========================================== [SUCCESS] Took 2.55 seconds =========================================================
```

<!-- Licencing Always at the Bottom -->
------------
### Licencing <img alt="" align="right" src="https://img.shields.io/badge/Licence-MIT-informational?style=flat&logoColor=white&color=FF9421" />

**MIT - LICENCE**

Copyright 2017 Seytonic, Spacehuhn
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions: 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. 

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 

* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
