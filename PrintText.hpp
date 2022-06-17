/**
* Compiler option to ensure that even if this header file is included in another file, it won't be placed multiple 
* times. If this does happen, then whenever a function or variable in this file is called, the program will see
* two locations to call from resulting in an error. Usually this is caught during compilation.
**/
#pragma once

//Foreground Color Codes
const uint8_t FOREGROUND_BLACK = 0x00;				//Black Font Color
const uint8_t FOREGROUND_BLUE = 0x01;				//Blue Font Color
const uint8_t FOREGROUND_GREEN = 0x02;				//Green Font Color
const uint8_t FOREGROUND_CYAN = 0x03;				//Cyan Font Color
const uint8_t FOREGROUND_RED = 0x04;				//Red Font Color
const uint8_t FOREGROUND_MAGENTA = 0x05;			//Magenta Font Color
const uint8_t FOREGROUND_BROWN = 0x06;				//Brown Font Color
const uint8_t FOREGROUND_LIGHTGRAY = 0x07;			//Light Gray Font Color
const uint8_t FOREGROUND_DARKGRAY = 0x08;			//Dark Gray Font Color
const uint8_t FOREGROUND_LIGHTBLUE = 0x09;			//Light Blue Font Color
const uint8_t FOREGROUND_LIGHTGREEN = 0x0A;			//Light Green Font Color
const uint8_t FOREGROUND_LIGHTCYAN = 0x0B;			//Light Cyan Font Color
const uint8_t FOREGROUND_LIGHTRED = 0x0C;			//Light Red Font Color
const uint8_t FOREGROUND_LIGHTMAGENTA = 0x0D;		//Light Magenta Font Color
const uint8_t FOREGROUND_YELLOW = 0x0E;				//Yellow Font Color
const uint8_t FOREGROUND_WHITE = 0x0F;				//White Font Color
	
//Background Color Codes
const uint8_t BACKGROUND_BLACK = 0x00;				//Black Background Color
const uint8_t BACKGROUND_BLUE = 0x10;				//Blue Background Color
const uint8_t BACKGROUND_GREEN = 0x20;				//Green Background Color
const uint8_t BACKGROUND_CYAN = 0x30;				//Cyan Background Color
const uint8_t BACKGROUND_RED = 0x40;				//Red Background Color
const uint8_t BACKGROUND_MAGENTA = 0x50;			//Magenta Background Color
const uint8_t BACKGROUND_BROWN = 0x60;				//Brown Background Color
const uint8_t BACKGROUND_LIGHTGRAY = 0x70;			//Light Gray Background Color
const uint8_t BACKGROUND_BLINKINGBLACK = 0x80;		//Blinking Black Background Color
const uint8_t BACKGROUND_BLINKINGBLUE = 0x90;		//Blinking Blue Background Color
const uint8_t BACKGROUND_BLINKINGGREEN = 0xA0;		//Blinking Green Background Color
const uint8_t BACKGROUND_BLINKINGCYAN = 0xB0;		//Blinking Cyan Background Color
const uint8_t BACKGROUND_BLINKINGRED = 0xC0;		//Blinking Red Background Color
const uint8_t BACKGROUND_BLINKINGMAGENTA = 0xD0;	//Blinking Magenta Background Color
const uint8_t BACKGROUND_BLINKINGYELLOW = 0xE0;		//Blinking Yellow Background Color
const uint8_t BACKGROUND_BLINKINGWHITE = 0xF0;		//Blinking White Background Color


//Definitions
#define VGA_MEMORY (uint8_t*)0xB8000			//Pointer to the start of screen RAM
#define VGA_WIDTH 0x50							//Width of the screen (80 Columns / 640x480 VGA)
#define BACKSPACE 0x8E							//Special Character Code for Backspace key
#define LEFT_SHIFT_PRESSED 0x2A					//Special Character Code for Left Shift key when pressed
#define LEFT_SHIFT_RELEASED 0xAA				//Special Character Code for Left Shift key when released
#define RIGHT_SHIFT_PRESSED 0x36				//Special Character Code for Right Shift key when pressed
#define RIGHT_SHIFT_RELEASED 0xB6				//Special Character Code for Right Shift key when released
#define CAPS_LOCK_PRESSED 0x3A					//Special Character Code for Caps Lock key when pressed
#define CAPS_LOCK_RELEASED 0xBA					//Special Character Code for Caps Lock key when released
#define ENTER 0x9C								//Special Character Code for Enter key