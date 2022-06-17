/**
* Compiler option to ensure that even if this header file is included in another file, it won't be placed multiple 
* times. If this does happen, then whenever a function or variable in this file is called, the program will see
* two locations to call from resulting in an error. Usually this is caught during compilation.
**/
#pragma once


//Libraries
#include "MemoryMap.cpp"
#include "PrintText.h"
#include "Typedefs.h"
#include "IDT.cpp"


//Constants
const uint8_t KEYBOARD_BUFFER_SIZE = 128;


//Global Variables
uint64_t command = 0;
uint8_t previousScanCode;
bool debugKB = false;
uint8_t debugKBNum = 0;
uint8_t commandArray[128];
uint8_t commandArrayIndex = 0;
uint8_t numChar = 0;


//In simple terms, this is just a string. I don't have access to any of the standard C++ libraries so the closest I can get to a string would
//be making an array of ASCII characters. To make it even more complicated, I can't have these values being read as a regular C++ integer, but
//as a uint8_t which is an 8-bit integer, so I have to typecast every single number in these arrays
uint8_t clearCommandArray[KEYBOARD_BUFFER_SIZE] 	= {(uint8_t)0x63, (uint8_t)0x6C, (uint8_t)0x65, (uint8_t)0x61, (uint8_t)0x72, (uint8_t)0x00, (uint8_t)0x00};
uint8_t aboutCommandArray[KEYBOARD_BUFFER_SIZE] 	= {(uint8_t)0x61, (uint8_t)0x62, (uint8_t)0x6F, (uint8_t)0x75, (uint8_t)0x74, (uint8_t)0x00, (uint8_t)0x00};
uint8_t restartCommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x72, (uint8_t)0x65, (uint8_t)0x73, (uint8_t)0x74, (uint8_t)0x61, (uint8_t)0x72, (uint8_t)0x74};
uint8_t debugKBCommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x64, (uint8_t)0x65, (uint8_t)0x62, (uint8_t)0x75, (uint8_t)0x67, (uint8_t)0x6B, (uint8_t)0x62};
uint8_t helpCommandArray[KEYBOARD_BUFFER_SIZE]		= {(uint8_t)0x68, (uint8_t)0x65, (uint8_t)0x6C, (uint8_t)0x70, (uint8_t)0x00, (uint8_t)0x00, (uint8_t)0x00};
uint8_t verCommandArray[KEYBOARD_BUFFER_SIZE]		= {(uint8_t)0x76, (uint8_t)0x65, (uint8_t)0x72, (uint8_t)0x00, (uint8_t)0x00, (uint8_t)0x00, (uint8_t)0x00};
uint8_t infoCommandArrau[KEYBOARD_BUFFER_SIZE]		= {(uint8_t)0x69, (uint8_t)0x6E, (uint8_t)0x66, (uint8_t)0x6F, (uint8_t)0x00, (uint8_t)0x00, (uint8_t)0x00};
uint8_t color0CommandArray[KEYBOARD_BUFFER_SIZE] 	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x30};
uint8_t color1CommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x31};
uint8_t color2CommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x32};
uint8_t color3CommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x33};
uint8_t color4CommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x34};
uint8_t color5CommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x35};
uint8_t color6CommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x36};
uint8_t color7CommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x37};
uint8_t color8CommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x38};
uint8_t color9CommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x39};
uint8_t colorACommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x61};
uint8_t colorBCommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x62};
uint8_t colorCCommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x63};
uint8_t colorDCommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x64};
uint8_t colorECommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x65};
uint8_t colorFCommandArray[KEYBOARD_BUFFER_SIZE]	= {(uint8_t)0x63, (uint8_t)0x6F, (uint8_t)0x6C, (uint8_t)0x6F, (uint8_t)0x72, (uint8_t)0x20, (uint8_t)0x66};