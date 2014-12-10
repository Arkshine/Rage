
#include <command/implementations/command_modules.h>
#include <util/util.h>
#include <global/global.h>

CommandModules::CommandModules(char* name) : Command(name)
{

}

void CommandModules::run()
{
	CVector<ModuleForRage*> modules = Global::modulesManager.get_vector();

	CVector<ModuleForRage*>::iterator current = modules.begin();

	Util::WriteToConsole("\nModules:\n\n");

	while(current != modules.end())
	{
		ModuleForRage* module = *(current++);

		Util::WriteToConsole("\tmodule: '%s'",module->get_name());
		Util::WriteToConsole(", version: '%s'",module->get_version());
		Util::WriteToConsole(", author: '%s'",module->get_author());
		Util::WriteToConsole("\n");
	}

	Util::WriteToConsole("\n");
}

void CommandModules::show_description()
{
	Util::WriteToConsole("shows modules");
}