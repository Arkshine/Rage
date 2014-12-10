
#include <commands_manager/commands_manager.h>
#include <global/global.h>

#include <command/implementations/command_handler.h>
#include <command/implementations/command_rage.h>
#include <command/implementations/command_errors.h>
#include <command/implementations/command_functions.h>
#include <command/implementations/command_modules.h>

void CommandsManager::load_commands()
{
	Global::commandsManager.add("rage",new CommandRage("rage"));
	Global::commandsManager.add("handlers",new CommandHandler("handlers"));
	Global::commandsManager.add("errors",new CommandErrors("errors"));
	Global::commandsManager.add("functions",new CommandFunctions("functions"));
	Global::commandsManager.add("modules",new CommandModules("modules"));
}
