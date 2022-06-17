/**
* Compiler option to ensure that even if this header file is included in another file, it won't be placed multiple
* times. If this does happen, then whenever a function or variable in this file is called, the program will see
* two locations to call from resulting in an error. Usually this is caught during compilation.
**/
#pragma once


//Libraries
#include "IO.cpp" 
#include "Typedefs.h"
#include "PrintText.h"


//Keyboard Scan Codes for a U.S. QWERTY keyboard
namespace USKeyboard
{
	const char ScanCodeLookupTable[] = {
	0, 0, '1', '2',
	'3', '4', '5', '6',
	'7', '8', '9', '0',
	'-', '=', 0, 0,
	'q', 'w', 'e', 'r',
	't', 'y', 'u', 'i',
	'o', 'p', '[', ']',
	0, 0, 'a', 's',
	'd', 'f', 'g', 'h',
	'j', 'k', 'l', ';',
	'\'', '`', 0, '\\',
	'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',',
	'.', '/', 0, '*',
	0, ' '
	};
}


//Global Variables
uint16_t CursorPosition;
uint8_t currentColor;
bool LeftShiftPressed = false;
bool RightShiftPressed = false;
bool CapsLockPressed = false;
uint8_t lastScanCode;
uint16_t capsLockPressCount = 0;


char hexToStringOutput[128];

//Converts any hex value (could be uint8_t, int_32_t, etc.) into a string
template<typename T>
const char* HexToString(T value)
{
	T* valPtr = &value;
	uint8_t* ptr;
	uint8_t temp;
	uint8_t size = (sizeof(T)) * 2 - 1;
	uint8_t i;
	for (i = 0; i < size; i++)
	{
		ptr = ((uint8_t*)valPtr + i);
		temp = ((*ptr & 0xF0) >> 4);
		hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
		temp = ((*ptr & 0x0F));
		hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
	}
	hexToStringOutput[size + 1] = 0;
	return hexToStringOutput;
}

char integerToStringOutput[128];

//Converts any integer value (could be uint8_t, int_32_t, etc.) into a string
template<typename T>
const char* IntegerToString(T value)
{
	uint8_t negativeNum = 0;
	if (value < 0)
	{
		negativeNum = 1;
		value *= -1;
		integerToStringOutput[0] = '-';
	}
	uint8_t size = 0;
	uint64_t sizeTester = (uint64_t)value;
	while (sizeTester / 10 > 0)
	{
		sizeTester /= 10;
		size++;
	}
	uint8_t index = 0;
	uint64_t newValue = (uint64_t)value;
	while (newValue / 10 > 0)
	{
		uint8_t remainder = newValue % 10;
		newValue /= 10;
		integerToStringOutput[negativeNum + size - index] = remainder + 48;
		index++;
	}
	uint8_t remainder = newValue % 10;
	integerToStringOutput[negativeNum + size - index] = remainder + 48;
	integerToStringOutput[negativeNum + size + 1] = 0;
	return integerToStringOutput;
}


void SetCursorPosition(uint16_t position)
{
	//Initializes where the blinking cursor starts 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(position & 0xFF));
	
	//Initializes where the blinking cursor ends
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
	
	//Sets the global variable of the cursor position to match the local variable
	CursorPosition = position;
}

void ClearScreen(uint64_t ClearColor = currentColor)
{
	uint64_t value = 0;
	value += ClearColor << 8;
	value += ClearColor << 24;
	value += ClearColor << 40;
	value += ClearColor << 56;
	
	//Repeats until all of the screen RAM is wiped
	for (uint64_t* i = (uint64_t*)VGA_MEMORY; i < (uint64_t*)(VGA_MEMORY + 4000); i++)
	{
		*i = value;
	}
	
	//Shifts cursor position all the way back to the top left 
	SetCursorPosition(0);
	
	//Sets the color in the parameter as the current color if specified
	currentColor = ClearColor;
}

//Returns a single number position from x and y coordinates
uint16_t PositionFromCoordinates(uint8_t x, uint8_t y)
{
	return y * VGA_WIDTH + x;
}


//Prints all contents of a string to the screen with whatever the current color is set as.
void PrintString(const char* string, uint8_t color = currentColor, bool changeColor = false)
{
	//Pointer to each character in the string (Very similar to a traversal)
	uint8_t* charPtr = (uint8_t*)string;

	//This variable allows the cursor position to be modified separately until the function is done.
	uint16_t index = CursorPosition;

	//Loops as long as the character pointer does not point to a null terminator in the string
	while (*charPtr != 0)
	{
		switch (*charPtr)
		{
		//Adds the width of the screen to the coordinates to shift the cursor one line down
		//when '\n' is located in the string being printed.
		case 10:
			index += VGA_WIDTH;
			break;

		//Finds the remainder of the cursor position and subtracts that from the total position
		//in order to shift the cursor all the way to the left
		case 13:									
			index -= index % VGA_WIDTH;
			break;

		//Prints out standard characters with color
		default:									
			*(VGA_MEMORY + index * 2) = *charPtr;
			*(VGA_MEMORY + index * 2 + 1) = color;
			index++;
			break;
		}
		charPtr++;
	}
	
	//Changes the color if the parameter is true
	if(changeColor) {
		currentColor = color;
	}
	SetCursorPosition(index);
}


//Outputs a single character to the terminal screen.
void PrintCharacter(char chr, uint8_t color = currentColor)
{
	*(VGA_MEMORY + CursorPosition * 2) = chr;				//Writes character code into Video Memory
	*(VGA_MEMORY + CursorPosition * 2 + 1) = color;			//Write color code into Video Memory
	SetCursorPosition(CursorPosition + 1);					//Shifts the cursor position once to the right
}