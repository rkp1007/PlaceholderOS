;Filename		|	RealModeFunctions.asm
;Author			|	Ryan Paradine
;Last Updated	|	6/07/22


;Prints a single character to the screen using BIOS functions only availible in Real Mode (16 bits)
PrintCharacter:
	;Pushes AX register onto stack
	push ax

	;Declaring 0x0E into the AH register will tell the BIOS to call the teletype output when interrupt 0x10 is called
	mov ah, 0x0e

	;Calls the video service interrupt
	int 0x10
	
	;Pops AX register off of the stack and returns label
	pop ax
	ret


;Moves cursor down one line and all the way to the left
PrintNewline:
	;Pushes AX register onto stack
	push ax

	;Line Feed code (Known as '\n' in higher level languages) which shifts the cursor down one line
	mov ax, 0xA						
	call PrintCharacter				

	;Carriage Return code (Known as '\r' in higher level languages) which shifts the cursor all the way to the left of the screen
	mov ax, 0xD						
	call PrintCharacter

	;Pops AX register off of the stack and returns label
	pop ax							
	ret


;Prints strings by getting the base address of the string and loops to print out each character (like a traversal)
PrintString:
	;Pushes the AX and BX register onto stack
	push ax
	push bx

	;Moves the string address into the 'BX' register
	mov bx, ax

	;Moves the character at the location of the pointer into the 'AX' register
	mov ax, [bx]

	;Adding a dot to a label inside of another label makes it a local label which is only accessible through the label 'PrintString'
	.loop:
		;Prints the character at the current pointer in the string
		call PrintCharacter

		;The pointer is incremented to move onto the next character
		inc bx

		;Once the string pointer is incremented, that character is loaded into the 'AX' register
		mov ax, [bx]

		;Compares the value that is located at the current string address to zero which indicates the string ended
		cmp al, 0
		
		;If those two values are not equal to each other, jump to the '.loop' label, otherwise continue
		jne .loop

		;Shifts the cursor down one line and all the way to the left to prepare for the next string
		call PrintNewline

		;Pops AX and BX register off of the stack and returns label
		pop ax
		pop bx
		ret
