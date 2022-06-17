//Compiler Options
#pragma once


//Libraries
#include "Typedefs.hpp"


//Constants for PIC chip
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1
#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01


//Outputs an 8-bit value into a port on the PIC chip
void outb(unsigned short port, unsigned char val)
{
	//Easy way to embed Assembly into a C++ program which calls the 'outb' opcode. The 'volatile'
	//keyword tells the compiler to not perform any optizations since it is very likely to break.
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}


//Reads a port on the PIC chip
unsigned char inb(unsigned short port)
{
	//Initializes a variable as a return value
	unsigned char returnValue;
	
	//Embeds the 'inb' opcode into this C++ function | Declared as volatile so there are no compiler optimizations
	asm volatile ("inb %1, %0"
		: "=a"(returnValue)
		: "Nd"(port));
	return returnValue;
}


//Remaps the entire PIC chip. Shoutout to OSDev.org which is where this function came from because I would not
//have figure this out on my own
//Source: https://wiki.osdev.org/PIC
void RemapPic()
{
	uint8_t a1, a2;
	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	outb(PIC1_DATA, 0);
	outb(PIC2_DATA, 8);
	outb(PIC1_DATA, 4);
	outb(PIC2_DATA, 2);
	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);
}

 static void StartSound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
    //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));
 
    //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
 }
 
 
  static void StopSound() {
	uint8_t tmp = inb(0x61) & 0xFC;
 	outb(0x61, tmp);
 }
