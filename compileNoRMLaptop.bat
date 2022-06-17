@ECHO off
nasm boot.asm -f bin -o boot.bin
echo [92m[ 17%% ][0m Complied Bootloader
nasm extended_program.asm -f elf64 -o extended_program.o
echo [92m[ 33%% ][0m Compiled Extended Program
nasm Binaries.asm -f elf64 -o Binaries.o
echo [92m[ 50%% ][0m Compiled Binaries
wsl $WSLENV/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Kernel.cpp" -o "Kernel.o"
echo [92m[ 66%% ][0m Compiled Kernel
wsl $WSLENV/x86_64-elf-ld --script="link.ld"
echo [92m[ 83%% ][0m Linked Project
copy /b boot.bin+kernel.bin GillOS.bin
echo [92m[ 100%% ][0m Done!
pause
start bochsrcLaptop.bxrc
cls