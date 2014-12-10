
#ifndef _INCLUDE_COMMAND_HANDLER_H_
#define _INCLUDE_COMMAND_HANDLER_H_

#include <command/command.h>

class CommandHandler : public Command
{
	public:

		CommandHandler(char* name);
		void run();
		void show_description();
};

#endif