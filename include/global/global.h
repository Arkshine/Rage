
#ifndef _INCLUDE_GLOBAL_
#define _INCLUDE_GLOBAL_

#include <handlers_manager/handlers_manager.h>
#include <commands_manager/commands_manager.h>
#include <libraries_manager/libraries_manager.h>
#include <functions_manager/functions_manager.h>
#include <patcher/patcher.h>
#include <trie/trie.h>
#include <hook/hook.h>
#include <stack/stack.h>
#include <function/function.h>
#include <error_manager/error_manager.h>
#include <sm_trie_tpl.h>
#include <function_creator/function_creator.h>
#include <modules_manager/modules_manager.h>
#include <rage/rage.h>
#include <virtual_functions_manager/virtual_functions_manager.h>
#include <handler_creator_manager/handler_creator_manager.h>

const bool CONTACT_RAGE_STAFF = true;

#ifdef WIN32
	#define RAGE_LIBRARY_EXTENSION "dll"
	#define RAGE_FILENAME_SEPARATOR '\\'
#else
	#define RAGE_LIBRARY_EXTENSION "so"
	#define RAGE_FILENAME_SEPARATOR '/'
#endif

namespace Global
{
	extern unsigned int CurrentFunctionID;
	extern unsigned int JumpSize;
	extern char Mod[100];
	extern HandlerManager handlerManager;
	extern CommandsManager commandsManager;
	extern LibrariesManager librariesManager;
	extern FunctionsManager functionsManager;	
	extern ErrorsManager errorsManager;
	extern Patcher patcher;
	extern Trie<Hook> hook_id_to_func;
	extern Stack<Function*> callStack;
	extern char OS[100];
	extern int PEV;
	extern KTrie<int> vtableOffsets;
	extern FunctionCreator functionCreator;
	extern ModulesManager modulesManager;
	extern Rage* rage;
	extern VirtualFunctionsManager virtualFunctionsManager;
	extern HandlerCreatorManager handlerCreatorManager;
	extern char* Alias;
};

#endif