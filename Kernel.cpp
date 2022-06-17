//Libraries
#include "Kernel.h"

//Binaries
	//extern const char Test[];


//Global Variables
uint8_t currentMenu = 0;	//Main Terminal


//Main Function
extern "C" void _start() {
	//Moves the cursor to the top left of the screen and the colors are set to a white foreground and black background
	SetCursorPosition(PositionFromCoordinates(0, 0));
	ClearScreen(BACKGROUND_BLACK | FOREGROUND_WHITE);
	
	//Initializes the Interrupt Descriptor Table
	InitializeIDT();
	
	//Makes a quick beep
	StartSound(1000);
	for(uint64_t time = 0; time < 10000000; time++);
	StopSound();
	
	//Launches the Terminal
	TerminalApp();
	return;
}