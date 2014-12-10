
#include <command/implementations/command_errors.h>
#include <util/util.h>
#include <global/global.h>

CommandErrors::CommandErrors(char* name) : Command(name)
{

}

void CommandErrors::run()
{
	Global::errorsManager.list();
}

void CommandErrors::show_description()
{
	Util::WriteToConsole("display errors");
}