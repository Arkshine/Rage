
#ifndef _INCLUDE_COMMANDS_MANAGER_H_
#define _INCLUDE_COMMANDS_MANAGER_H_

#include <command/command.h>
#include <manager/manager.h>

class CommandsManager : public Manager<Command*>
{
	public:
		static void load_commands();
};



#endif