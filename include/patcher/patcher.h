
#ifndef __PATCHER_H__
#define __PATCHER_H__

#include <function/function.h>

#include <memory/memory.h>

class Patcher
{
	private:

		Function* do_patch_safe(void* address,HandlerForRage* handler,unsigned int id,char* func_name,Library* library);

	public:

		Function* do_patch(void* address,HandlerForRage* handler,unsigned int id,char* func_name,Library* library);
		Function* do_patch_virtual(void* address, void** address_in_table, HandlerForRage* handler, unsigned int id,char* func_name,char* class_name,Library* library);
};

#endif