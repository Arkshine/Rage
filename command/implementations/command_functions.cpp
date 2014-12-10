
#include <command/implementations/command_functions.h>
#include <util/util.h>
#include <global/global.h>

CommandFunctions::CommandFunctions(char* name) : Command(name)
{

}

void CommandFunctions::run()
{
	Global::functionsManager.list();
}

void CommandFunctions::show_description()
{
	Util::WriteToConsole("display functions");
}