
#ifndef __FUNCTION_HANDLER_H__
#define __FUNCTION_HANDLER_H__

#include <CVector.h>
#include "amxxmodule.h"

class HandlerForRage;

class FunctionForHandler
{
	public:

		virtual void* get_original_address() = 0;
		virtual void* get_managed_address() = 0;
		virtual void pre_call() = 0;
		virtual void post_call() = 0;
		virtual CVector<int>* get_plugin_hooks() = 0;
		virtual CVector<void*>* get_module_hooks() = 0;
		virtual HandlerForRage* get_handler() = 0;
};

#endif
