//Libraries
#include "Terminal.h"


//The 'Restart()' function was written using Assembly, so it must be declared as an external
//function so that this C++ file knows how to handle it during compilation
extern "C" void Restart();


//Cycles through the keyboard array and the array for the command (basically a string) and returns a boolean
//value whether or not both arrays contain the same values
bool CheckMatch(uint8_t keyboardArray[], uint8_t commandArray[])
{
	uint8_t index = 0;
	while (index < 128)
	{
		if (keyboardArray[index] != commandArray[index])
		{
			return false;
		}
		index++;
	}
	return true;
}


//Functions
void FindApplication(uint64_t charSum)
{
	//Sorry that this looks like a mess, but it is the easiest way to implement considering that I have
	//rewritten the keyboard handler more than I am willing to admit
	if(CheckMatch(commandArray, clearCommandArray))
	{
		ClearScreen();
	}
	else if(CheckMatch(commandArray, aboutCommandArray)) 
	{
		PrintString("\n\n\rThis is a project created by Ryan Paradine for AP Computer Science Principles\n\r\
which shows my best attempt at creating an Operating System. While this OS\n\r\
was very difficult to create, it still needs lots of improvement and is\n\r\
nowhere near as complex as an Operating System such as Windows 11 & macOS.\n\r");
	}
	else if(CheckMatch(commandArray, restartCommandArray))
	{
		Restart();
	}
	else if(CheckMatch(commandArray, helpCommandArray))
	{
		
	}
	else if(CheckMatch(commandArray, verCommandArray))
	{
		PrintString("\n\rPlaceholderOS [version 0.2.1]");
	}
	else if(CheckMatch(commandArray, color0CommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_BLACK, true);
	} 
	else if(CheckMatch(commandArray, color1CommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_BLUE, true);
	} 
	else if(CheckMatch(commandArray, color2CommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_GREEN, true);
	} 
	else if(CheckMatch(commandArray, color3CommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_CYAN, true);
	}
	else if(CheckMatch(commandArray, color4CommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_RED, true);
	} 
	else if(CheckMatch(commandArray, color5CommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_MAGENTA, true);
	}
	else if(CheckMatch(commandArray, color6CommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_BROWN, true);
	} 
	else if(CheckMatch(commandArray, color7CommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_LIGHTGRAY, true);
	} 
	else if(CheckMatch(commandArray, color8CommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_DARKGRAY, true);
	} 
	else if(CheckMatch(commandArray, color9CommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_LIGHTBLUE, true);
	}
	else if(CheckMatch(commandArray, colorACommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_LIGHTGREEN, true);
	}
	else if(CheckMatch(commandArray, colorBCommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_LIGHTCYAN, true);
	}
	else if(CheckMatch(commandArray, colorCCommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_LIGHTRED, true);
	}
	else if(CheckMatch(commandArray, colorDCommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_LIGHTMAGENTA, true);
	}
	else if(CheckMatch(commandArray, colorECommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_YELLOW, true);
	}
	else if(CheckMatch(commandArray, colorFCommandArray))
	{
		PrintString("", BACKGROUND_BLACK | FOREGROUND_WHITE, true);
	}
	else if(CheckMatch(commandArray, debugKBCommandArray))
	{
		if(debugKBNum % 2 == 0)
		{
			PrintString("\n\r*KEYBOARD DEBUG MODE STARTED*\n\r");
			debugKBNum++;
			debugKB = true;
		} else {
			PrintString("\n\r*EXITED KEYBOARD DEBUG MODE*");
			debugKBNum++;
			debugKB = false;
		}
	} else {
		PrintString("\n\r*SYNTAX ERROR*");
	}
}


void DebugKeyboard(bool debug = false)
{
	if(debug) {
		PrintString("\n\r----------------------------------------\n\r** COMMAND CODE ** : 0x");
		PrintString(HexToString(command));
		PrintString("\n\r----------------------------------------");
	}
}


//Handles regular characters with a scan code and character code
void StandardTerminalKeyboardHandler(uint8_t scanCode, uint8_t chr)
{
	if(numChar > 128)
	{
		//Clears the keyboard array
		for (uint8_t t = 0; t < 128; t++)
		{
			commandArray[t] = (uint8_t)0x00;
		}
		
		//Initializes Error Environment
		ClearScreen(BACKGROUND_BLUE | FOREGROUND_WHITE);
		SetCursorPosition(CursorPosition + 25);
		PrintString("Error 0x01: CHARACTER OVERFLOW\n\n\n\r", BACKGROUND_BLACK | FOREGROUND_WHITE, true);
		PrintString("   The keyboard buffer for character codes is only 128 bytes in this operating\n\rsystem due to size constrants. Once a command has a length larger than that, it\n\rescapes the array possibly causing damage to other code. This is known as a \n\rcode injection which is a major security concern and is why the computer is\n\rtnow halted and cannot continue to run.\n\r", BACKGROUND_BLUE | FOREGROUND_WHITE, true);
		SetCursorPosition(CursorPosition + 21);
		PrintString("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n*PLEASE RESTART YOUR MACHINE MANUALLY*");
		commandArrayIndex = 0;
		numChar = 0;
		while(true);		//Does absolutely nothing and acts like the computer is halted by infinitely looping.
	}
	if (chr != 0)
	{
		switch (LeftShiftPressed | RightShiftPressed)
		{
		case true:
			PrintCharacter(chr - 32, currentColor);
			commandArray[commandArrayIndex] = chr;
			commandArrayIndex++;
			numChar++;
			break;

		case false:
			PrintCharacter(chr, currentColor);
			commandArray[commandArrayIndex] = chr;
			commandArrayIndex++;
			numChar++;
			break;
		}
	}
	else {
		switch (scanCode)
		{
		//Handles Backspace Key when pressed
		case BACKSPACE:
			SetCursorPosition(CursorPosition - 1);
			PrintCharacter(' ', currentColor);
			SetCursorPosition(CursorPosition - 1);
			commandArray[commandArrayIndex] = (uint8_t)0x00;
			commandArrayIndex--;
			break;

		//Handles Left Shift Key when pressed
		case LEFT_SHIFT_PRESSED:		//Left Shift Pressed
			LeftShiftPressed = true;
			break;

		//Handles Left Shift Key when released
		case LEFT_SHIFT_RELEASED:		//Left Shift Released
			LeftShiftPressed = false;
			break;

		//Handles Right Shift Key when pressed
		case RIGHT_SHIFT_PRESSED:		//Right Shift Pressed
			RightShiftPressed = true;
			break;
		
		//Handles Right Shift Key when released
		case RIGHT_SHIFT_RELEASED:		//Right Shift Released
			RightShiftPressed = false;
			break;

		//Handles Enter Key when pressed
		case ENTER:						
			FindApplication(command);
			DebugKeyboard(debugKB);
			PrintString("\n\r> ");
			for (uint8_t j = 0; j < 128; j++)
			{
				commandArray[j] = (uint8_t)0x00;
			}
			commandArrayIndex = 0;
			break;

		default:
			break;
		}
		previousScanCode = scanCode;
	}
}


//Handles characters with no character codes, only scan codes
void SpecialTerminalKeyboardHandler(uint8_t scanCode)
{
	switch (scanCode)
	{
	case 0x4B:
		SetCursorPosition(CursorPosition - 1);
		break;
	case 0x4D:
		SetCursorPosition(CursorPosition + 1);
		break;
	default:
		break;
	}
}

void TerminalKeyboardHandler(uint8_t scanCode, uint8_t chr)
{
	if (lastScanCode == 0xE0)
	{
		SpecialTerminalKeyboardHandler(scanCode);
	}
	else {
		StandardTerminalKeyboardHandler(scanCode, chr);
	}
	lastScanCode = scanCode;
}

//Main Function
void TerminalApp()
{
	MainKeyboardHandler = TerminalKeyboardHandler;
	PrintString("PlaceholderOS [version 0.2.1]\n\r(c) Ryan Paradine. All Rights Reserved.\n\r> ");
}