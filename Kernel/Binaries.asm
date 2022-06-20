;Filename		|	Binaries.asm
;Author			|	Ryan Paradine
;Last Updated	|	6/06/22


;This macro allows binary files to be included into the operating system, however
;I do not have enough time to actually implement this so it is unused as of right now
%macro IncBin 2
	SECTION .rodata
	GLOBAL %1
%1:
	incbin %2
	db 0
	%1_size: dq %1_size - %1
%endmacro

;Tells the compiler to implement 'test.txt' into the operating system
IncBin Test, "test.txt"