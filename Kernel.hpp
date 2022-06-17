/**
* Compiler option to ensure that even if this header file is included in another file, it won't be placed multiple 
* times. If this does happen, then whenever a function or variable in this file is called, the program will see
* two locations to call from resulting in an error. Usually this is caught during compilation.
**/
#pragma once


//Libraries needed for 'Kernel.cpp'
#include "PrintText.cpp"
#include "MemoryMap.cpp"
#include "Typedefs.hpp"
#include "IO.cpp"
#include "IDT.cpp"
#include "Terminal.cpp"