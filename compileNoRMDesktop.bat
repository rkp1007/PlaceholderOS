@ECHO off
nasm boot.asm -f bin -o boot.bin
echo [92m[ 13%% ][0m Complied Bootloader
nasm extended_program.asm -f elf64 -o extended_program.o
echo [92m[ 25%% ][0m Compiled Extended Program
nasm Binaries.asm -f elf64 -o Binaries.o
echo [92m[ 38%% ][0m Compiled Binaries
wsl $WSLENV/gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Kernel.cpp" -o "Kernel.o"
echo [92m[ 50%% ][0m Compiled Kernel
wsl $WSLENV/x86_64-elf-ld --script="link.ld"
@copy /b boot.bin+kernel.bin PlaceholderOS.bin >NUL
echo [92m[ 63%% ][0m Linked Project
del "boot.bin"
del "Kernel.bin"
echo [92m[ 75%% ][0m Deleted Binaries
del "Binaries.o"
del "extended_program.o"
del "Kernel.o"
echo [92m[ 88%% ][0m Deleted Object Files
echo [92m[ 100%% ][0m Deleted Temporary Files
pause
start bochsrcDesktop.bxrc
cls