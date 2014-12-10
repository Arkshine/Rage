
#include <global/global.h>

namespace Global
{
	unsigned int CurrentFunctionID;
	unsigned int JumpSize = 5;
	char Mod[100];
	HandlerManager handlerManager;
	CommandsManager commandsManager;
	LibrariesManager librariesManager;
	FunctionsManager functionsManager;	
	ErrorsManager errorsManager;
	Patcher patcher;
	Trie<Hook> hook_id_to_func;
	Stack<Function*> callStack;
#if defined __linux__
	char OS[] = "linux";
#else
	char OS[] = "windows";
#endif
	int PEV;
	KTrie<int> vtableOffsets;
	FunctionCreator functionCreator;
	ModulesManager modulesManager;
	Rage* rage = new Rage();
	VirtualFunctionsManager virtualFunctionsManager;
	HandlerCreatorManager handlerCreatorManager;
	char* Alias = NULL;
}
