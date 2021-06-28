# BAD USB <img align="right" src="https://github.com/CrashOverrideProductions/Bad_USB/blob/main/images/logo.jpg?raw=true">

### Project: Arduino Based Malicious USB <img alt="" align="right" src="https://img.shields.io/badge/Status-Prototype%20Phase-informational?style=flat&logoColor=white&color=73398D" />


<!-- Repo Cover Image -->
<p style="background-color:rgba(22,22,22,1.00)" align="center">
<img align="center" src="https://github.com/CrashOverrideProductions/Bad_USB/blob/main/images/background.jpg?raw=true" />
</p>

<!-- Repo Stats -->
<img align="center" src="https://img.shields.io/github/commit-activity/m/CrashOverrideProductions/Bad_USB"> <img align="center" src="https://img.shields.io/github/last-commit/CrashOverrideProductions/Bad_USB"> <img align="center" src="https://img.shields.io/github/languages/code-size/CrashOverrideProductions/Bad_USB"> <img align="center" src="https://img.shields.io/github/directory-file-count/CrashOverrideProductions/Bad_USB">

### Details
The BadUSB is intended to be a budget alternative to the current offering of Keystroke Injection tools available on the market.

### What is a Keystroke Injection Attack?
A Keystroke Injection Attack Tool is a specially designed USB device, often disguised as a thumb drive, that automatically runs code on any host computer into which it is plugged. It does so by appearing to the computer as a USB HID ('Human Interface Device') keyboard and/or mouse, and then “typing” in keyboard shortcuts and commands.

This can be a vector for malicious code, and is potentially dangerous and destructive! This project aims to educate you and your “victim” on the dangers of these devices. Nothing is quite so memorable a lesson in security as plugging in an innocent looking device and being met with a flurry of terminal windows and text popping up, and receiving an automatically deployed desktop background that says “You just go PWND, be more careful next time!"

---
<!-- To Do List -->
### To Do List
- [x] Complete Readme.md
- [x] Build & Test Prototype
- [x] Design Schematic
- [x] Finalise Software
- [x] Design Board
- [ ] Order Prototype PCBs
- [ ] Design 3D Print Shell
- [ ] Research Injection Moulded Shell

---
### Prototype PCB Design
<img align="center" src="https://github.com/CrashOverrideProductions/Bad_USB/blob/main/images/BadUSB-TOP.png?raw=true" /> <img align="center" src="https://github.com/CrashOverrideProductions/Bad_USB/blob/main/images/BadUSB-Bottom.png?raw=true" />
##### BOM

| Part# | Part                                                              | Mouser Part#       | Qty | Price   | Total   |
| ----- | ----------------------------------------------------------------- | ------------------ | :-: | :-----: | ------: |
| C1    | Multilayer Ceramic Capacitors MLCC - SMD/SMT 16V 1uF X7R 0603 10% | 80-C0603C105K4R    | 1   | $0.1350 | $0.1350 |
| C2,C3	| Multilayer Ceramic Capacitors MLCC - SMD/SMT 10V 10uF 0603 10%    | 791-0603X106K100CT | 2   | $0.1490 | $0.2980 |
| IC1   | 8-bit Microcontrollers - MCU AVR USB 32K FLASH INDUSTRIAL         | 556-ATMEGA32U4-AU	 | 1   | $5.9500 | $5.9500 |
| IC2   | LDO Voltage Regulators 300mA High Speed Votage Regulator          | 865-XC6219A332MR-G | 1   | $0.9450 | $0.9450 |
| J2    | USB Connectors USB 2.0 type A plug 4 pin Horizontal TH            | 490-UP2-AH-1-TH	 | 1   | $0.7970 | $0.7970 |
| J4    | Headers & Wire Housings Micro Low Profile Header Strips           | 200-FTS10301LDVTR	 | 1   | $2.1600 | $2.1600 |
| MICRO-SD| Memory Card Connectors TFR READER (HINGE TYPE)                  | 538-47219-2001	 | 1   |$1.9400	 |$1.9400  |
| R1,R2 |Thin Film Resistors - SMD 0603 50ppm 22Ohm                         | 603-RT0603DRE0722RL| 2   |$0.1760  |$0.3520  |
|       |                                                                   |  TOTAL AUD         |     |         |$12.5770 |


---
### Arduino Leonardo Prototype Details
##### Hardware
| Part Number  | Item                                                       |  Qty   | Price AUD$ |
| ------------ | ---------------------------------------------------------- | :----: | ---------: |
| A000057      | AVR Arduino Leonardo with Headers                          | 1      | $26.73     |
| DEV-12761    | Memory IC Development Tools microSD Shield Shield          | 1      | $21.53     |

##### Software
The software for this project is a modified version of the Malduino Elite firmware developed by [Seytonic](https://github.com/Seytonic "Seytonic") released under the MIT Licence.

##### Hardware Configuration
| Signal   | Uno Pin | Leonardo Pin |
| -------- | :-----: | :----------: |
|SD Select | D10     | D10          |
|MISO      | D12     | ICSP MISO    |
|MOSI      | D11     | ICSP MOSI    |
|SCK       | D13     | ICSP SCK     | 

| Notes |
| ------------ |
| Arduino Leonardo does not map SPI pins to D11/D12/D13 like the uno therefore some jumper wires are required |

---
### Proof of Concept 
Images / Screenshots, etc
##### Images
![](https://github.com/CrashOverrideProductions/Bad_USB/blob/main/images/prototype.jpg?raw=true) 
##### Screenshots
![](https://github.com/CrashOverrideProductions/Bad_USB/blob/main/images/test1.jpg?raw=true) 

![](https://github.com/CrashOverrideProductions/Bad_USB/blob/main/images/test2.jpg?raw=true)
##### Sample Ducky Script
- Spoiler Alert - This is the Rick Roll Script
        
        DELAY 400
        GUI r
        DELAY 250
        STRING https://www.youtube.com/watch?v=dQw4w9WgXcQ
        ENTER
        DELAY 3000
        STRING f


<!-- Licencing Always at the Bottom -->
------------
### Licencing <img alt="" align="right" src="https://img.shields.io/badge/Licence-CC--BY--NC--SA--4.0-informational?style=flat&logo=Creative%20Commons&logoColor=white&color=EF9421" />

**Creative Commons: Attribution - NonCommercial - ShareAlike 4.0 International (CC BY-NC-SA 4.0)**


**You are free to:**

**Share** — copy and redistribute the material in any medium or format

**Adapt** — remix, transform, and build upon the material


**Under the following terms:**

**Attribution** — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.

**NonCommercial** — You may not use the material for commercial purposes.

**ShareAlike** — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.

No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.
