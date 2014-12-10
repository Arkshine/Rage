
#ifndef _INCLUDE_HANDLER_FOR_RAGE__H_
#define _INCLUDE_HANDLER_FOR_RAGE__H_

#include "amxxmodule.h"

#include <function/function_for_handler.h>

class HandlerForRage
{
	public:
		
		virtual char* get_name() = 0;

		virtual void* get_gate_address() = 0;
		
		virtual int create_plugin_hook(AMX*,const char*) = 0;

		virtual cell rage_call(FunctionForHandler* function,AMX* amx,cell* params) = 0;
		virtual cell rage_set_param(AMX* amx,cell* params) = 0;
		virtual cell rage_set_return(AMX* amx,cell* params) = 0;
		virtual cell rage_get_return(AMX* amx,cell* params) = 0;

		virtual int AMXX_Detach() = 0;
		virtual int AMXX_PluginsLoaded() = 0;
		virtual void AMXX_PluginsUnloaded() = 0;
		virtual void AMXX_PluginsUnloading() = 0;
};

#endif
