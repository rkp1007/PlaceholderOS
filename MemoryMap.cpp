/**
* NOTE: I should update the 'PrintMemoryMap' functions because it was made before the majority
* of functions located in PrintText.cpp which is much better organized.
**/


/**
* Compiler option to ensure that even if this header file is included in another file, it won't be placed multiple 
* times. If this does happen, then whenever a function or variable in this file is called, the program will see
* two locations to call from resulting in an error. Usually this is caught during compilation.
**/
#pragma once

//Libraries
#include "PrintText.cpp"
#include "Typedefs.h"

//Structure for memory regions
struct MemoryMapEntry {
	uint64_t BaseAddress;
	uint64_t RegionLength;
	uint32_t RegionType;
	uint32_t ExtendedAttributes;
};

extern uint8_t MemoryRegionCount;		//An external variable from an Assembly file that counts the total memory regions
uint8_t FreeMemoryRegionCount;			//A variable to count the number of free memory regions
MemoryMapEntry* FreeMemory[10];			//Initializes an array of 10 memory map entries for free space


//Function used to debug issues with the memory mapping system. Provides information such as the
//memory pointer base, region length, region type, and attributes stored in the structure
void PrintMemoryMap(MemoryMapEntry* memoryMap, uint16_t position)
{
	//Initializes the cursor position
	SetCursorPosition(position);

	//
	PrintString("Memory Base: ");
	PrintString(IntegerToString(memoryMap->BaseAddress));
	SetCursorPosition(position + (VGA_WIDTH * 1));
	
	PrintString("Region Length: ");
	PrintString(IntegerToString(memoryMap->RegionLength));
	SetCursorPosition(position + (VGA_WIDTH * 2));

	PrintString("Region Type: ");
	PrintString(IntegerToString(memoryMap->RegionType));
	SetCursorPosition(position + (VGA_WIDTH * 3));

	PrintString("Memory Attributes: ");
	PrintString(HexToString(memoryMap->ExtendedAttributes));
	SetCursorPosition(position + (VGA_WIDTH * 5));
}

//A variable which tells the operating system if it has already calculated the memory map
bool CalculatedMemoryRegions = false;


//Traverses through each region and storing its information in the memory map array
MemoryMapEntry** ReadFreeMemoryRegions()
{
	//Exits if the memory map has already been calculated
	if (CalculatedMemoryRegions)
	{
		return FreeMemory;
	}
	
	//Initializes an index for the memory region traversal
	uint8_t FreeMemoryIndex;
	
	//Traverses through the memory regions determine whether or not it is reserved or free
	for (uint8_t i = 0; i < MemoryRegionCount; i++)
	{
		MemoryMapEntry* memoryMap = (MemoryMapEntry*)0x5000;
		memoryMap += i;
		if (memoryMap->RegionType == 1)
		{
			FreeMemory[FreeMemoryIndex] = memoryMap;
			FreeMemoryIndex++;
		}
	}
	FreeMemoryRegionCount = FreeMemoryIndex;
	CalculatedMemoryRegions = true;
	return FreeMemory;
}
