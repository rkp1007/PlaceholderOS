;Filename		|	DiskFunctions.asm
;Author			|	Ryan Paradine
;Last Updated	|	5/28/22


;Compiler Macros
SECTOR_2 equ 0x8000


ReadDisk:
	mov ah, 0x02				;Specifies to the BIOS that the read sectors interrupt is requested when interrupt 0x13 is called
	mov bx, SECTOR_2			;Specifies where the data from the disk will be stored into memory
	mov al, 0x40				;Specifies how many sectors to read | 64 Sectors X 512 Bytes = 32768 Bytes / 32 Kilobytes
	mov dl, [BOOT_DISK]			;Specifies what drive to read from
	mov ch, 0					;Specifies which cylinder will be used
	mov dh, 0					;Specifies which head will be reading the sectors
	mov cl, 2					;Specifies which sector to begin reading from (starts from one, not zero for some weird reason)
	
	;An interrupt which calls sector based hard drive and floppy disk services
	int 0x13
	
	;If for whatever reason the BIOS could not read the disk, the carry flag is set and this conditional jump will handle the error. If not
	;the label will be returned and the bootloader will jump to the next sector.
	jc DiskReadFailed
	ret


;An exception to handle the failure for the operating system to read the disk
DiskReadFailed:
	;Points to the location of the string and prints it
	mov ax, DiskErrorMsg			
	call PrintString

	;Jumps to this same line forever in order to prevent the processor from halting
	jmp $


;Specifies which Hard Drive will be used in the operating system
BOOT_DISK:
	db 0


;Strings
DiskErrorMsg:
	db "Disk Read Failed", 0