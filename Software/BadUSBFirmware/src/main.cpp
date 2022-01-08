// |------------------------------- HEADER ---------------------------------------------------------------------------------------------------------|
// APPLICATION:      MALDUINO ELITE - FIRMWARE

// AUTHOR:           SEYTONIC, SPACEHUNN

// MODIFIED BY:      JUSTIN BLAND
// PURPOSE OF MOD:   MINOR ALTERATIONS TO SUIT CRASHOVERRIDE BADUSB

// DATE:             09/12/2020
// AUDIT DATE:       18/04/2021
// STATUS:           PLATFORMIO MIGRATION
//
// LICENCE:          MIT LICENCE
//
// DESIGNED MCU 1:     TEST - ARDUINO LEONARDO R3 (ATMEGA32U4) | PRODUCTION - ATMEGA32U4
// DESIGNED MCU 2:     TEST - SEEEDUINO ZERO (ATMEGA SAMD21) | PRODUCTION - ATMEGA SAMD21E...
//
// REVISIONS:
//                   09/12/2020  IMPORT MALDUINO ELITE SOURCE FROM SEYTONIC'S GITHUB REPOSITORY
//                   09/12/2020  ADD HEADER & LICENCE DETAILS
//                   09/12/2020  REMOVE DIP SWTICH | FILENAME = "ducky.txt"
//                   10/12/2020  REMOVE LED | ADD TEST PINOUT + TEST SUCCESSFUL
//                   28/10/2020  ADD VID/PID HELPFUL INFO
//                   18/04/2021  CAST 'buf' & 'repeatBuffer' (char*)malloc....
//                   18/04/2021  MOVE 'runLine' FUNCTION BELOW 'runCommand' FUNCION - PLATFORMIO ISSUE
//                   30/04/2021  IMPLEMENT 'NumLock', 'Pause/Break', 'Scroll-Lock', 'F13 - F23' KEYS
//                   08/07/2021  ADD AMTEL SAMD21 TO BUILD ENVELOPE
//                   08/01/2022  DEFINE CS PIN D10 (10)
//                               ADD Demo Payload

// |------------------------------- LICENCE INFO ---------------------------------------------------------------------------------------------------|
/*
Copyright 2017 Seytonic, Spacehuhn

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/


// |------------------------------- HELPFUL INFO ---------------------------------------------------------------------------------------------------|
// ARDUINO LEONARDO DOES NOT MAP SPI PINS TO D11 / D12 / D13 
//
//  LEONARDO R3 PIN CONFIGURATION
//  |-----SIGNAL-----|--UNO--|--LEONARDO--|
//   SD Card Select     D10        D10
//   MISO               D12     ICSP MISO
//   MOSI               D11     ISCP MOSI
//   SCK                D13     ISCP SCK

// SEEEDUINO ZERO (ATMEGA SAMD21) PIN CONFIGURATION
// |-----SIGNAL-----|--PIN--|
//  SD Card Select     D10
//  MISO               D22
//  MOSI               D23
//  SCK                D24

//  VENDOR AND DEVICE IDS FOR COMMON HID DEVICES
//  |--MANUFACTURER--|--------------DESCRIPTION--------------|--VENDOR ID--|--DEVICE ID--|
//        APPLE                MAGIC KEYBOARD A1644               05AC          0267
//        APPLE                  MAGIC MOUSE A1269                05AC          030D
//      MICROSOFT                 SURFACE KEYBAORD                045E          07CD
//      MICROSOFT                WIRED KEYBAORD 400               045E          0752
//      MICROSOFT               CLASSIC INTELLIMOUSE              045E          0823

//          

// |------------------------------- DEFINITIONS ----------------------------------------------------------------------------------------------------|

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Mouse.h>
#include <Keyboard.h>

//#define debug true // <-- uncomment to turn serial output on
#define CSpin D10 //Chip-Select of the SD-Card reader

#define buffersize 256

#define KEYPAD_0 234
#define KEYPAD_1 225
#define KEYPAD_2 226
#define KEYPAD_3 227
#define KEYPAD_4 228
#define KEYPAD_5 229
#define KEYPAD_6 230
#define KEYPAD_7 231
#define KEYPAD_8 232
#define KEYPAD_9 233
#define KEYPAD_ASTERIX 221
#define KEYPAD_ENTER 224
#define KEYPAD_MINUS 222
#define KEYPAD_PERIOD 235
#define KEYPAD_PLUS 223
#define KEYPAD_SLASH 220
#define PRINTSCREEN 206 
#define NUM_LOCK 219
#define SCROLL_LOCK 207
#define PAUSE_BTN 208

File payload;

char* buf = (char*)malloc(sizeof(char) * buffersize);
char* repeatBuffer = (char*)malloc(sizeof(char) * 12);

int bufSize = 0;
int defaultDelay = 5;
int defaultCharDelay = 5;
int rMin = -100;
int rMax = 100;
int ledFlash = 500;

void DemoPayload()
{
    #ifdef debug 
    Serial.print("Sending Demo Payload.......");
    #endif
    
    delay(defaultDelay);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.print("r");
    Keyboard.releaseAll();
  
    delay(200);
    Keyboard.print("www.github.com/CrashOverrideProductions");

    delay(200);
    Keyboard.press(KEYPAD_ENTER);

    Keyboard.releaseAll();

    #ifdef debug 
    Serial.println("Sent");
    #endif
}


int getSpace(int start, int end) {
    for (int i = start; i < end; i++) {
        if (buf[i] == ' ') return i;
    }
    return -1;
}

bool equals(char* strA, int start, int end, char* strB, int strLen) {
    if (end - start != strLen) return false;
    for (int i = 0; i < strLen; i++) {
        if (strA[start + i] != strB[i]) return false;
    }
    return true;
}

int toPositive(int num) {
    if (num < 0) return num * (-1);
    else return num;
}

bool equalsBuffer(int start, int end, char* str) { return equals(buf, start, end, str, String(str).length()); }

int getInt(char* str, int pos) {
    if (equals(str, pos + 1, pos + 7, "RANDOM", 6)) {
        return random(rMin, rMax);
    }
    else {
        return String(str).substring(pos + 1, pos + 6).toInt();
    }
}

void KeyboardWrite(uint8_t c) {
    Keyboard.press(c);
    delay(defaultCharDelay);
    Keyboard.release(c);
}

void runCommand(int s, int e) {
#ifdef debug 
    Serial.println("Press '" + String(buf).substring(s, e) + "'");
#endif

    if (e - s < 2) Keyboard.press(buf[s]);
    else if (equalsBuffer(s, e, "ENTER")) Keyboard.press(KEY_RETURN);
    else if (equalsBuffer(s, e, "GUI") || equalsBuffer(s, e, "WINDOWS")) Keyboard.press(KEY_LEFT_GUI);
    else if (equalsBuffer(s, e, "SHIFT")) Keyboard.press(KEY_LEFT_SHIFT);
    else if (equalsBuffer(s, e, "ALT") || equalsBuffer(s, e, "ALT_LEFT") || equalsBuffer(s, e, "ALTLEFT")) Keyboard.press(KEY_LEFT_ALT);
    else if (equalsBuffer(s, e, "ALT_RIGHT") || equalsBuffer(s, e, "ALTRIGHT")) Keyboard.press(KEY_RIGHT_ALT);
    else if (equalsBuffer(s, e, "CTRL") || equalsBuffer(s, e, "CONTROL")) Keyboard.press(KEY_LEFT_CTRL);
    else if (equalsBuffer(s, e, "CAPSLOCK")) Keyboard.press(KEY_CAPS_LOCK);
    else if (equalsBuffer(s, e, "DELETE")) Keyboard.press(KEY_DELETE);
    else if (equalsBuffer(s, e, "END")) Keyboard.press(KEY_END);
    else if (equalsBuffer(s, e, "ESC") || equalsBuffer(s, e, "ESCAPE")) Keyboard.press(KEY_ESC);
    else if (equalsBuffer(s, e, "HOME")) Keyboard.press(KEY_HOME);
    else if (equalsBuffer(s, e, "INSERT")) Keyboard.press(KEY_INSERT);
    else if (equalsBuffer(s, e, "PAGEUP")) Keyboard.press(KEY_PAGE_UP);
    else if (equalsBuffer(s, e, "PAGEDOWN")) Keyboard.press(KEY_PAGE_DOWN);
    else if (equalsBuffer(s, e, "SPACE")) Keyboard.press(' ');
    else if (equalsBuffer(s, e, "TAB")) Keyboard.press(KEY_TAB);
    else if (equalsBuffer(s, e, "BACKSPACE")) Keyboard.press(KEY_BACKSPACE);

    else if (equalsBuffer(s, e, "UP") || equalsBuffer(s, e, "UPARROW")) Keyboard.press(KEY_UP_ARROW);
    else if (equalsBuffer(s, e, "DOWN") || equalsBuffer(s, e, "DOWNARROW")) Keyboard.press(KEY_DOWN_ARROW);
    else if (equalsBuffer(s, e, "LEFT") || equalsBuffer(s, e, "LEFTARROW")) Keyboard.press(KEY_LEFT_ARROW);
    else if (equalsBuffer(s, e, "RIGHT") || equalsBuffer(s, e, "RIGHTARROW")) Keyboard.press(KEY_RIGHT_ARROW);

    else if (equalsBuffer(s, e, "PRINTSCREEN")) Keyboard.press(PRINTSCREEN);

    else if (equalsBuffer(s, e, "F1")) Keyboard.press(KEY_F1);
    else if (equalsBuffer(s, e, "F2")) Keyboard.press(KEY_F2);
    else if (equalsBuffer(s, e, "F3")) Keyboard.press(KEY_F3);
    else if (equalsBuffer(s, e, "F4")) Keyboard.press(KEY_F4);
    else if (equalsBuffer(s, e, "F5")) Keyboard.press(KEY_F5);
    else if (equalsBuffer(s, e, "F6")) Keyboard.press(KEY_F6);
    else if (equalsBuffer(s, e, "F7")) Keyboard.press(KEY_F7);
    else if (equalsBuffer(s, e, "F8")) Keyboard.press(KEY_F8);
    else if (equalsBuffer(s, e, "F9")) Keyboard.press(KEY_F9);
    else if (equalsBuffer(s, e, "F10")) Keyboard.press(KEY_F10);
    else if (equalsBuffer(s, e, "F11")) Keyboard.press(KEY_F11);
    else if (equalsBuffer(s, e, "F12")) Keyboard.press(KEY_F12);
    else if (equalsBuffer(s, e, "F13")) Keyboard.press(KEY_F13);
    else if (equalsBuffer(s, e, "F14")) Keyboard.press(KEY_F14);
    else if (equalsBuffer(s, e, "F15")) Keyboard.press(KEY_F15);
    else if (equalsBuffer(s, e, "F16")) Keyboard.press(KEY_F16);
    else if (equalsBuffer(s, e, "F17")) Keyboard.press(KEY_F17);
    else if (equalsBuffer(s, e, "F18")) Keyboard.press(KEY_F18);
    else if (equalsBuffer(s, e, "F19")) Keyboard.press(KEY_F19);
    else if (equalsBuffer(s, e, "F20")) Keyboard.press(KEY_F20);
    else if (equalsBuffer(s, e, "F21")) Keyboard.press(KEY_F21);
    else if (equalsBuffer(s, e, "F22")) Keyboard.press(KEY_F22);
    else if (equalsBuffer(s, e, "F23")) Keyboard.press(KEY_F23);
    else if (equalsBuffer(s, e, "F24")) Keyboard.press(KEY_F24);

    else if (equalsBuffer(s, e, "NUM_0")) KeyboardWrite(KEYPAD_0);
    else if (equalsBuffer(s, e, "NUM_1")) KeyboardWrite(KEYPAD_1);
    else if (equalsBuffer(s, e, "NUM_2")) KeyboardWrite(KEYPAD_2);
    else if (equalsBuffer(s, e, "NUM_3")) KeyboardWrite(KEYPAD_3);
    else if (equalsBuffer(s, e, "NUM_4")) KeyboardWrite(KEYPAD_4);
    else if (equalsBuffer(s, e, "NUM_5")) KeyboardWrite(KEYPAD_5);
    else if (equalsBuffer(s, e, "NUM_6")) KeyboardWrite(KEYPAD_6);
    else if (equalsBuffer(s, e, "NUM_7")) KeyboardWrite(KEYPAD_7);
    else if (equalsBuffer(s, e, "NUM_8")) KeyboardWrite(KEYPAD_8);
    else if (equalsBuffer(s, e, "NUM_9")) KeyboardWrite(KEYPAD_9);
    else if (equalsBuffer(s, e, "NUM_ASTERIX")) KeyboardWrite(KEYPAD_ASTERIX);
    else if (equalsBuffer(s, e, "NUM_ENTER")) KeyboardWrite(KEYPAD_ENTER);
    else if (equalsBuffer(s, e, "NUM_Minus")) KeyboardWrite(KEYPAD_MINUS);
    else if (equalsBuffer(s, e, "NUM_PERIOD")) KeyboardWrite(KEYPAD_PERIOD);
    else if (equalsBuffer(s, e, "NUM_PLUS")) KeyboardWrite(KEYPAD_PLUS);
    else if (equalsBuffer(s, e, "NUMLOCK")) Keyboard.press(NUM_LOCK);
    else if (equalsBuffer(s, e, "SCROLLLOCK")) Keyboard.press(SCROLL_LOCK);
    else if (equalsBuffer(s, e, "BREAK") || equalsBuffer(s, e, "PAUSE")) Keyboard.press(PAUSE_BTN);



    else if (equalsBuffer(s, e, "CLICK") || equalsBuffer(s, e, "CLICK_LEFT") || equalsBuffer(s, e, "MOUSECLICK")) Mouse.click();
    else if (equalsBuffer(s, e, "CLICK_RIGHT")) Mouse.click(MOUSE_RIGHT);
    else if (equalsBuffer(s, e, "CLICK_MIDDLE")) Mouse.click(MOUSE_MIDDLE);

    else if (equalsBuffer(s, e, "PRESS") || equalsBuffer(s, e, "PRESS_LEFT")) Mouse.press();
    else if (equalsBuffer(s, e, "PRESS_LEFT")) Mouse.press(MOUSE_RIGHT);
    else if (equalsBuffer(s, e, "PRESS_MIDDLE")) Mouse.press(MOUSE_MIDDLE);
    else if (equalsBuffer(s, e, "RELEASE") || equalsBuffer(s, e, "RELEASE_LEFT")) Mouse.release();
    else if (equalsBuffer(s, e, "RELEASE_LEFT")) Mouse.release(MOUSE_RIGHT);
    else if (equalsBuffer(s, e, "RELEASE_MIDDLE")) Mouse.release(MOUSE_MIDDLE);

#ifdef debug
    else Serial.println("failed to find command");
#endif
    /* not implemented
    else if(equalsBuffer(s,e,"APP")) Keyboard.press();
    else if(equalsBuffer(s,e,"MENU")) Keyboard.press(327);
    */
}

void runLine() {
#ifdef debug 
    Serial.println("run: '" + String(buf).substring(0, bufSize) + "' (" + (String)bufSize + ")");
#endif

    int space = getSpace(0, bufSize);

      if(space == -1) runCommand(0,bufSize);

    else {
        if (equalsBuffer(0, space, "DEFAULTDELAY") || equalsBuffer(0, space, "DEFAULT_DELAY"))
         defaultDelay = getInt(buf, space);
        else if (equalsBuffer(0, space, "DEFAULTCHARDELAY") || equalsBuffer(0, space, "DEFAULT_CHAR_DELAY")) defaultCharDelay = getInt(buf, space);
        else if (equalsBuffer(0, space, "DELAY")) delay(getInt(buf, space));
        else if (equalsBuffer(0, space, "STRING")) {
            for (int i = space + 1; i < bufSize; i++) KeyboardWrite(buf[i]);
        }
        else if (equalsBuffer(0, space, "MOUSE")) {
            int nSpace = getSpace(space + 1, bufSize);
            int x = getInt(buf, space);
            int y = getInt(buf, nSpace);
            Mouse.move(x, y);
            #ifdef debug 
                Serial.println("Move mouse " + (String)x + " " + (String)y);
            #endif
        }
        else if (equalsBuffer(0, space, "SCROLL")) Mouse.move(0, 0, getInt(buf, space));
        else if (equalsBuffer(0, space, "RANDOMMIN")) rMin = getInt(buf, space);
        else if (equalsBuffer(0, space, "RANDOMMAX")) rMax = getInt(buf, space);
        else if (equalsBuffer(0, space, "REM") || equalsBuffer(0, space, "REPEAT")) {}
        else{
            runCommand(0,space);
            while(space >= 0 && space < bufSize){
                int nSpace = getSpace(space+1,bufSize);
                if(nSpace == -1) nSpace = bufSize;
                runCommand(space+1,nSpace);
                space = nSpace;
            }
        }
    }

    Keyboard.releaseAll();
    delay(defaultDelay);
}

void setup() {
    #ifdef debug
        Serial.begin(9600);
        delay(2000);
        Serial.println("Started!");
    #endif
    pinMode(CSpin, OUTPUT);
    randomSeed(analogRead(0));


    if (!SD.begin(CSpin)) {
        #ifdef debug 
            Serial.println("No SD Card Found... Running Demo Ducky Script");
        #endif

        DemoPayload();
        return;
    }
    else 
    {
        #ifdef debug 
            Serial.println("Accessing ducky.txt from SD Card");
        #endif
        payload = SD.open("ducky.txt");
    }




    if (!payload)
    {
        Serial.println("No Payload Found");
        return;
    }
    else {
        Keyboard.begin();
        Mouse.begin();
        while (payload.available()) {

            buf[bufSize] = payload.read();
            if (buf[bufSize] == '\r' || buf[bufSize] == '\n' || bufSize >= buffersize)
            {
                if (buf[bufSize] == '\r' && payload.peek() == '\n')
                {
                 payload.read();
                }

                //---------REPEAT---------     
                int repeatBufferSize = 0;
                int repeats = 0;
                unsigned long payloadPosition = payload.position();

                for (int i = 0; i < 12; i++) {
                    if (payload.available()) {
                        repeatBuffer[repeatBufferSize] = payload.read();
                        repeatBufferSize++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (repeatBufferSize > 6) 
                {
                    if (equals(repeatBuffer, 0, 6, "REPEAT", 6)) 
                    {
                        repeats = getInt(repeatBuffer, 6);
                    }
                }

                for (int i = 0; i < repeats; i++) 
                {
                runLine();
                }

                payload.seek(payloadPosition);
                //------------------------

                runLine();
                bufSize = 0;
            }
            else bufSize++;
        }
        if (bufSize > 0) {
            runLine();
            bufSize = 0;
        }
        payload.close();
        Mouse.end();
        Keyboard.end();
    }
}

void loop()
{
    // led flash here
    delay(ledFlash);

}