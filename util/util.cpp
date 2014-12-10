
#include <util/util.h>

namespace Util
{
	void WriteToFile(char* format,...)
	{
		va_list argptr;
		va_start(argptr,format);

		FILE* f = fopen("rage_debug.txt","a+");
		vfprintf(f,format,argptr);
		fprintf(f,"\n");
		fclose(f);

		va_end(argptr);
	}

	void WriteToConsole(char* format,...)
	{
		va_list argptr;
		va_start(argptr,format);
	
		static char msg[1000];
		vsprintf(msg,format,argptr);

		g_engfuncs.pfnServerPrint(msg);

		va_end(argptr);
	}

	void WriteToConsoleLine(char* format,...)
	{
		va_list argptr;
		va_start(argptr,format);
	
		static char msg[1000];
		vsprintf(msg,format,argptr);

		g_engfuncs.pfnServerPrint(msg);
		g_engfuncs.pfnServerPrint("\n");

		va_end(argptr);
	}
};