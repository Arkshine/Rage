
#ifndef __FUNCTION_BASE_H__
#define __FUNCTION_BASE_H__

#include <function/function_for_handler.h>
#include <function/function_for_module.h>
#include <handler/handler_for_rage.h>
#include <CVector.h>
#include <util/util.h>
#include <library/library.h>

#include "amxxmodule.h"

class Function : public FunctionForModule, public FunctionForHandler
{
	protected :

		void* original_address;
		void* managed_address;

		HandlerForRage* handler;

		CVector<int> hooks[2];
		CVector<void*> hooks_modules[2];

		Library* library;

	public:

		Function(void* original_address,void* managed_address,HandlerForRage* handler,Library* library);
		void* get_original_address();
		void* get_managed_address();
		HandlerForRage* get_handler();
		int add_plugin_hook(AMX* amx,const char* function_name,int phase);
		bool remove_plugin_hook(int hook,int phase);
		void clear_plugin_hooks();
		CVector<int>* get_plugin_hooks();

		virtual void show_description() = 0;
		
		void add_module_hook(void* address,RageHookPhase rage_hook_phase);
		bool remove_module_hook(void* address,RageHookPhase rage_hook_phase);
		CVector<void*>* get_module_hooks();
 
		Library* get_library();
};

#endif
