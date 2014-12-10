
#ifndef _INCLUDE_COMMAND_MODULES_H_
#define _INCLUDE_COMMAND_MODULES_H_

#include <command/command.h>

class CommandModules : public Command
{
	public:

		CommandModules(char* name);
		void run();
		void show_description();
};

#endif