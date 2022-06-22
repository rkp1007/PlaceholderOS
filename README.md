# PlaceholderOS
This project will be my best attempt at creating an operating system from the ground up. This 
includes the bootloader, memory maps, keyboard handler, kernel, etc. Despite the fact that 
a project like this can never be truly completed, my main goal is to allow programs to be
written for the operating system without the author directly adding it to the source code.


## How to run PlaceholderOS

- Download the source code
- Download and Install Bochs [here](https://sourceforge.net/projects/bochs/)
- Open Bochs and click 'Disk & Boot' in the Edit Options
- Specify the type of floopy drive as a '3.5" 1.44M'
- Set the floppy image / device path to wherever 'PlaceholderOS.bin' is
- Set the type of floppy media as '1.44M' and change status to 'inserted'
- Click Ok and then go to 'Keyboard & Mouse'
- Set the 'Keyboard serial delay' to 5 and click Ok
- Save the configuration and open it to use the operating system


## Upcoming Plans

- Figure out how to interface with the Time-Stamp counter to make delays
- Find a better way to interface with the PC speaker
- Add some arithmetic commands to the terminal
- Make a universal makefile for anyone who wants to compile
- Reorganize code in some files since I was originally put under a time constraint to finish this project
