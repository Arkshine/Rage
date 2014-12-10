
#ifndef _INCLUDE_VIRTUAL_FUNCTION_
#define _INCLUDE_VIRTUAL_FUNCTION_

#include <handler_creator/handler_creator_for_rage.h>
#include <virtual_function/virtual_function_for_module.h>
#include <function/function_for_module.h>
#include <library/library.h>

class VirtualFunction : public VirtualFunctionForModule
{
	private:

		HandlerCreatorForRage* handler_creator;
		int vtable_offset;
		int offset;
		char* func_name;
		Library* library;

	public:

		VirtualFunction(char* func_name,HandlerCreatorForRage* handler_creator,int vtable_offset,int offset,Library* library);

		unsigned int create_get_id(void* object);
		unsigned int create_get_id(void* object,char* class_name);

		FunctionForModule* create_with_object(void* object);
		FunctionForModule* create_with_class(char* class_name);

		char* get_name();
		Library* get_library();
};

#endif