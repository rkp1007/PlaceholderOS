;Filename		|	DiskFunctions.asm
;Author			|	Ryan Paradine
;Last Updated	|	6/02/22


jmp EnterPM

;16-bit Libraries
%include "GDT.asm"
%include "RealModeFunctions.asm"
%include "DetectMemory.asm"


;Compiler Macros
SCREEN_RAM equ 0xB8000


;Enters Protected Mode on the CPU
EnterPM:
	call DetectMemory			;Finds what memory regions can be written to
	call EnableA20				;Enables Bit 20 on the address line in order to access higher amounts of memory
	cli							;Clears the Interrupt Flag
	lgdt [gdt_descriptor]		;Loads the Global Descriptor Table
	mov eax, cr0				;Moves the control register into 'EAX' register
	or eax, 1					;Applies an inclusive or with the value 1 and 'EAX'
	mov cr0, eax				;Moves the value in the 'EAX' register into the control register
	jmp codeseg:StartPM			;Ready to access Protected Mode features


;Since the original Intel 8086, 8088, and 80186 had twenty address lines so it could access about a megabyte
;of memory, but only had 16-bit registers so some math and bit-shifting had to be done in order to access
;all addresses. The common theme throughout the development of this operating system is that no matter how
;useless some features on CPU's are today, they are still kept in for backwards compatiblity which means that
;I have to enable this gate in order to access a reasonable amount of memory.
EnableA20:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret


[bits 32]

;32-bit Libraries
%include "CPUID.asm"
%include "SimplePaging.asm"

StartPM:
	;Initializes all of the registers needed
	mov ax, dataseg
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	call DetectCPUID			;Checks if CPUID is available on the processor
	call DetectLongMode			;Checks if Long Mode is available on the processor
	call SetupIdentityPaging	;Sets up Identity Paging which is how the operating system will read memory
	call EditGDT				
	jmp codeseg:Start64Bit		;Ready to enable Long Mode

[bits 64]
[extern	_start]

;64-bit Libraries
%include "IDT.asm"


;Attempts to enter long mode on the CPU
Start64Bit:
	mov edi, SCREEN_RAM					;Points to the address for screen RAM in the 'EDI' index register
	mov rax, 0x0F200F200F200F20			;(VGA Color Code + 1?????) + (Character Code) * 4 | Prints out black background, white foreground, no text
	mov ecx, 500						;The 'ECX' register is a parameter for the 'rep' opcode to count how many loops will occur
	rep stosq							;Repeatedly stores the value in 'EAX' to SCREEN_RAM which is going to clear the screen
	call ActivateSEE					;Enables the SIMD instructions on this CPU
	call _start							;Now that Long Mode is accessible, the OS is now ready to go into the kernel.
	jmp $


;SEE is a feature which adds SIMD (single input, multiple data) instructions which can help increase
;data throughput. I don't plan on using these instructions myself, but it is possible that the GCC 
;compiler will use these instructions to optimize my C++ code.
ActivateSEE:
	mov rax, cr0
	and ax, 0b11111101
	or ax, 0b00000001
	mov cr0, rax
	mov rax, cr4
	or ax, 0b1100000000
	mov cr4, rax
	ret


;Allocates four sectors for this code by filling the end of the code and the end of the four
;sectors with zeros.
times 2048-($-$$) db 0