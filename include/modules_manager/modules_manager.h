
#ifndef _INCLUDE_MODULES_MANAGER_H_
#define _INCLUDE_MODULES_MANAGER_H_

#include <module/module_for_rage.h>
#include <manager/manager.h>

#include <library/library_for_module.h>
#include <function/function_for_module.h>

class ModulesManager : public Manager<ModuleForRage*>
{
	public:

		void AmxxAttach(PFN_REQ_FNPTR reqFnptrFunc);
		void AmxxDetach();
		void PluginsLoaded();
		void PluginsUnloading();
		void PluginsUnloaded();
		void LoadedLibrary(LibraryForModule* library);
		void LoadedFunction(FunctionForModule* function);
		void LoadedVirtualFunction(VirtualFunctionForModule* virtual_function);

		static void load_new_modules();

};

#endif