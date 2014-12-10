
#include "amxxmodule.h"
#include <error_manager/error_manager.h>
#include <util/util.h>

void ErrorsManager::add_error(char* format,...)
{
	va_list argptr;
	va_start(argptr,format);
	
	char* msg = new char[200];
	vsprintf(msg,format,argptr);

	this->errors.push_back(msg);

	va_end(argptr);
}

void ErrorsManager::list()
{
	CVector<char*>::iterator it = this->errors.begin();

	Util::WriteToConsole("\nErrors:\n\n");

	while(it != this->errors.end())
	{
		char* error = *(it++);
		Util::WriteToConsole("\t%s\n",error);
	}

	Util::WriteToConsole("\n");
}