
#ifndef __FUNCTION_MODULE_H__
#define __FUNCTION_MODULE_H__

#include <CVector.h>
#include "amxxmodule.h"
#include <rage/rage_hook_phase.h>

#include <library/library_for_module.h>

class FunctionForModule
{
	public:

		virtual void* get_original_address() = 0;
		virtual void* get_managed_address() = 0;
		virtual void add_module_hook(void* address,RageHookPhase rage_hook_phase) = 0;
		virtual bool remove_module_hook(void* address,RageHookPhase rage_hook_phase) = 0;
		virtual char* get_name() = 0;
		virtual LibraryForModule* get_library() = 0;

};

#endif