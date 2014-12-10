
#include <command/implementations/command_rage.h>
#include <util/util.h>
#include <global/global.h>

CommandRage::CommandRage(char* name) : Command(name)
{

}

void CommandRage::run()
{
	CVector<Command*> commands = Global::commandsManager.get_vector();

	CVector<Command*>::iterator it = commands.begin();


	Util::WriteToConsole("\nRage Commands:\n\n");

	while(it != commands.end())
	{
		Command* command = *(it++);

		Util::WriteToConsole("%s :\t",command->get_name());
		command->show_description();
		Util::WriteToConsoleLine("");
	}

	Util::WriteToConsole("\n");
}

void CommandRage::show_description()
{
	Util::WriteToConsole("shows this");
}