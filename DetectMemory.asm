;Filename		|	DetectMemory.asm
;Author			|	Ryan Paradine
;Last Updated	|	6/03/22


;Variable to count the number of memory regions
MemoryRegionCount:
	db 0
	GLOBAL MemoryRegionCount


;This is a BIOS function to tell the operating system how much memory there is
;in a PC. Not only does it specifically state whether it is reserved or not, but
;it can also read higher memory addresses than the 32-bit limit (4 Gigabytes).
DetectMemory:
	;Initalizing Registers
	mov ax, 0
	mov es, ax
	mov di, 0x5000
	mov edx, 0x534D4150
	xor ebx, ebx
	
	.DMLoop:
		;Parameter to tell BIOS the exact interrupt to be called in '0x15'
		mov eax, 0xE820
		
		;Parameter to specify size of buffer for the return values
		mov ecx, 24
		
		;Calls Interrupt 0x15
		int 0x15
		
		;Compares the 'EBX' register to zero.
		cmp ebx, 0
		
		;If the two values are equal to each other, jump to the end of the function
		je .EndDMFunction
		
		;Adds 24 to the buffer for results
		add di, 24
		
		;Increment the MemoryRegionCount variable
		inc byte [MemoryRegionCount]
		
		;Jump back up to '.DMLoop' to read more memory regions
		jmp .DMLoop
	.EndDMFunction:
		ret