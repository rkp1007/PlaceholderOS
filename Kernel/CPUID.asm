;Filename		|	CPUID.asm
;Author			|	Ryan Paradine
;Last Updated	|	6/06/22


;What if the CPU had an opcode to call for the CPU info which could be stored in a register or
;memory address. Well, the Intel engineers decided that it would be too easy which is why this
;mess of a label exists. This label checks the CPUID to ensure that the CPU being used has the
;features nessesary to run my operating system. Shoutout to OSDev.org which helped me out with this.
DetectCPUID:
	pushfd					;Pushes EFLAGS onto the stack
	pop eax					;Pops the 'EAX' register off of the stack
	mov ecx, eax			;Moves the contents from the 'EAX' register to the 'ECX' register
	xor eax, 1 << 21		;Applies an exclusive OR between 'EAX' and 1 bit-shifted to the right 21 times
	push eax				;Pushes the 'EAX' register onto the stack
	popfd					;Pops EFLAGS off of the stack
	pushfd					;Pushes EFLAGS onto the stack
	pop eax					;Pops the 'EAX' register off of the stack
	push eax				;Pushes the 'EAX' register onto the stack
	popfd					;Pops EFLAGS off of the stack
	xor eax, ecx			;Applies an exclusive OR between the 'EAX' and 'ECX' register
	jz NoCPUID				;Jumps to the label 'NoCPUID' if the zero flag is set
	ret

;
DetectLongMode:
	mov eax, 0x80000001		;This memory address can only be accessed if this CPU has long mode
	cpuid					;Idenifies the CPU
	test edx, 1 << 29		;Tests the LM-bit which tells the computer whether or not this CPU supports long mode
	jz NoLongMode			;The processor is halted if there is no long mode
	ret

NoLongMode:
	hlt

NoCPUID:
	hlt