
#ifndef __MODULE_MODULE_FOR_RAGE_H__
#define __MODULE_MODULE_FOR_RAGE_H__

#include "amxxmodule.h"
#include <library/library_for_module.h>
#include <function/function_for_module.h>
#include <virtual_function/virtual_function_for_module.h>
#include <function_incomplete/function_incomplete_for_module.h>

class ModuleForRage
{
	public:

		virtual char* get_name() = 0;
		virtual char* get_author() = 0;
		virtual char* get_version() = 0;

		virtual void LoadedLibrary(LibraryForModule* library) = 0;
		virtual void LoadedFunction(FunctionForModule* function) = 0;
		virtual void LoadedVirtualFunction(VirtualFunctionForModule* virtual_function) = 0;
		virtual void LoadedFunctionIncomplete(FunctionIncompleteForModule* function_incomplete) = 0;

		virtual int AMXX_Attach(PFN_REQ_FNPTR reqFnptrFunc) = 0;
		virtual int AMXX_Detach() = 0;
		virtual int AMXX_PluginsLoaded() = 0;
		virtual void AMXX_PluginsUnloaded() = 0;
		virtual void AMXX_PluginsUnloading() = 0;
};

#endif
