/**
* Compiler option to ensure that even if this header file is included in another file, it won't be inserted multiple 
* times in the program. If this does happen, then whenever a function or variable in this file is called, the program
* will see two locations to call from resulting in an error. Usually this is caught during compilation.
**/
#pragma once

//Libraries
#include "Typedefs.hpp"
#include "IO.cpp" 
#include "PrintText.cpp"


//Forms a binary structure of the Interrupt Descriptor Table
struct IDT64
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t ist;
	uint8_t types_attr;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t zero;
};

extern IDT64 _idt[256];
extern uint64_t isr1;
extern "C" void LoadIDT();

void InitializeIDT()
{
	//Sets the reserved section to zero
	_idt[1].zero = 0x00000000;
	
	//The offset is determined by 'isr1' which is then manipulated and bitshifted
	_idt[1].offset_low = (uint16_t)(((uint64_t)&isr1 & 0x000000000000FFFF));
	_idt[1].offset_mid = (uint16_t)(((uint64_t)&isr1 & 0x00000000FFFF0000) >> 16);
	_idt[1].offset_high = (uint32_t)(((uint64_t)&isr1 & 0xFFFFFFFF00000000) >> 32);
	
	//The IST structure is set to zero
	_idt[1].ist = 0x00;
	
	//Selects 0x08 as the code segment to be read
	_idt[1].selector = 0x08;
	
	//Setup to specifically initalize the 64-bit interrupt gate
	_idt[1].types_attr = 0x8E;
	
	//
	RemapPic();
	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	LoadIDT();
}

void (*MainKeyboardHandler)(uint8_t scanCode, uint8_t chr);


//Handles all interrupts invoked by the keyboard
extern "C" void isr1_handler()
{
	uint8_t scanCode = inb(0x60);							//Reads port 0x60 for the keyboard scan code
	uint8_t chr = 0;										//Initialize variable to setup character
	
	//If the scan code is higher than 0x3A, assign a character 
	if (scanCode < 0x3A)
	{
		chr = USKeyboard::ScanCodeLookupTable[scanCode];
	}
	if (MainKeyboardHandler != 0)
	{
		MainKeyboardHandler(scanCode, chr);
	}
	outb(0x20, 0x20);
	outb(0xa0, 0x20);
}
