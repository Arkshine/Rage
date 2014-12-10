
#ifndef _INCLUDE_COMMAND_ERROR_H_
#define _INCLUDE_COMMAND_ERROR_H_

#include <command/command.h>

class CommandErrors : public Command
{
	public:

		CommandErrors(char* name);
		void run();
		void show_description();
};

#endif