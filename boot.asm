;Filename		|	boot.asm
;Author			|	Ryan Paradine
;Last Updated	|	5/28/22


;This is the memory address where the boot sector will be located at
[org 0x7c00]

;Start of Boot Sector
start:
	;On startup, the BIOS stores the disk number into register 'DL' which is moved into the 'BOOT_DRIVE' variable
	mov [BOOT_DISK], dl

	;Declaring the top of the stack being at 0x7C00 (The stack descends, not ascends)
	mov bp, 0x7c00

	;Sets the stack pointer register to the base address 0x7C00
	mov sp, bp

	;Prints out messages to screen to log what is being done
	mov ax, StartMSG
	call PrintString
	mov ax, EnteringProtectedModeMSG
	call PrintString

	;Loads data from disk into memory and jumps there
	call ReadDisk
	jmp SECTOR_2


;Include Files
%include "RealModeFunctions.asm"
%include "DiskFunctions.asm"

;Strings
StartMSG:	db "Currently in 16 bit Real Mode", 0
EnteringProtectedModeMSG:	db "Entering 32 bit Protected Mode", 0

;End of boot sector
times 510-($-$$) db 0
dw 0xaa55