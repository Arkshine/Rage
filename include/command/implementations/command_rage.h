
#ifndef _INCLUDE_COMMAND_RAGE_H_
#define _INCLUDE_COMMAND_RAGE_H_

#include <command/command.h>

class CommandRage : public Command
{
	public:

		CommandRage(char* name);
		void run();
		void show_description();
};

#endif