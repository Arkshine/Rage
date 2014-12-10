
#ifndef __UTIL_H__
#define __UTIL_H__

#include "amxxmodule.h"

namespace Util
{
	extern void WriteToFile(char* format,...);
	extern void WriteToConsole(char* format,...);
	extern void WriteToConsoleLine(char* format,...);
};

#endif