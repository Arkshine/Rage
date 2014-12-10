
#ifndef _INCLUDE_COMMAND_FUNCTIONS_H_
#define _INCLUDE_COMMAND_FUNCTIONS_H_

#include <command/command.h>

class CommandFunctions : public Command
{
	public:

		CommandFunctions(char* name);
		void run();
		void show_description();
};

#endif