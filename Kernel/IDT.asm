;Filename		|	IDT.asm
;Author			|	Ryan Paradine
;Last Updated	|	6/06/22


[extern _idt]
idtDescriptor:
	dw 4095
	dq _idt

;Macro to push all registers onto the stack
%macro PUSHALL 0
	push rax
	push rcx
	push rdx
	push r8
	push r9
	push r10
	push r11
%endmacro

;Macro to pop all of the registers off of the stack
%macro POPALL 0
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdx
	pop rcx
	pop rax
%endmacro

[extern	isr1_handler]
isr1:
	PUSHALL					;Pushes all of the registers onto the stack
	call isr1_handler		;Calls the keyboard handler
	POPALL					;Pops all registers off of the stack
	iretq					;Returns from interrupt
	GLOBAL isr1				;Declares 'isr1' as a global label


;Loads the Interrupt Descriptor Table
LoadIDT:
	lidt[idtDescriptor]				;Loads the IDT Descriptor Table address into the IDT Register
	sti								;Enables the Interrupt Flag
	ret
	GLOBAL LoadIDT					;Declares LoadIDT a global function so that it could be accessed

;Simply restarts the computer
Restart:
	;Pushes all of the registers onto the stack
	PUSHALL
	
	;Parameters to restart the computer in interrupt 0x15
	mov ax, 0x5307
	mov bx, 0x0001
	mov cx, 0x0003
	
	;Calls interrupt 0x15
	int 0x15
	
	;Pops all of the registers off of the stack
	POPALL
	
	ret
	
	;Declares this a global function
	GLOBAL Restart