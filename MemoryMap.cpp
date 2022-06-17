//Compiler Options
#pragma once

//Libraries
#include "PrintText.cpp"
#include "Typedefs.h"

struct MemoryMapEntry {
	uint64_t BaseAddress;
	uint64_t RegionLength;
	uint32_t RegionType;
	uint32_t ExtendedAttributes;
};

extern uint8_t MemoryRegionCount;
uint8_t FreeMemoryRegionCount;
MemoryMapEntry* FreeMemory[10];

void PrintMemoryMap(MemoryMapEntry* memoryMap, uint16_t position)
{
	SetCursorPosition(position);

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

bool MemoryRegionsGot = false;

MemoryMapEntry** ReadFreeMemoryRegions()
{
	if (MemoryRegionsGot)
	{
		return FreeMemory;
	}
	uint8_t FreeMemoryIndex;
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
	MemoryRegionsGot = true;
	return FreeMemory;
}