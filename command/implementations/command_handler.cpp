
#include <command/implementations/command_handler.h>
#include <util/util.h>
#include <global/global.h>

CommandHandler::CommandHandler(char* name) : Command(name)
{

}

void CommandHandler::run()
{
	CVector<HandlerCreatorForRage*> handler_creators = Global::handlerCreatorManager.get_vector();

	CVector<HandlerCreatorForRage*>::iterator current = handler_creators.begin();

	Util::WriteToConsole("\nHandlers:\n\n");

	while(current != handler_creators.end())
	{
		HandlerCreatorForRage* handler_creator = *(current++);

		Util::WriteToConsole("\thandler: '%s'",handler_creator->get_name());
		Util::WriteToConsole(", version: '%s'",handler_creator->get_version());
		Util::WriteToConsole(", author: '%s'",handler_creator->get_author());
		Util::WriteToConsole("\n");
	}

	Util::WriteToConsole("\n");
}

void CommandHandler::show_description()
{
	Util::WriteToConsole("shows the loaded handlers");
}