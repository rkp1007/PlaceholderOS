/**
* Compiler option to ensure that even if this header file is included in another file, it won't be placed multiple
* times. If this does happen, then whenever a function or variable in this file is called, the program will see
* two locations to call from resulting in an error. Usually this is caught during compilation.
**/
#pragma once

//Custom Variable Types
typedef unsigned char uint8_t;				//Unsigned 8-bit Integer	| 0 : 255
typedef signed char int8_t;					//Signed 8-bit Integer		| -128 : 127
typedef unsigned short uint16_t;			//Unsigned 16-bit Integer	| 0 : 65,535
typedef signed short int16_t;				//Signed 16-bit Integer		| -32,768 : 32,767
typedef unsigned int uint32_t;				//Unsigned 32-bit Integer	| 0 : 4,294,967,296
typedef signed int int32_t;					//Signed 32-bit Integer		| -2,147,483,648 : 2,147,483,647
typedef unsigned long long uint64_t;		//Unsigned 64-bit Integer	| 0 : 18,446,744,073,709,551,616
typedef signed long long int64_t;			//Signed 64-bit Integer		| -9,223,372,036,854,775,808 : 9,223,372,036,854,775,807