
#ifndef _INCLUDE_VIRTUAL_FUNCTION_FOR_MODULE
#define _INCLUDE_VIRTUAL_FUNCTION_FOR_MODULE

#include <function/function_for_module.h>

class VirtualFunctionForModule
{
	public:
		virtual char* get_name() = 0;

		virtual FunctionForModule* create_with_object(void* object) = 0;
		virtual FunctionForModule* create_with_class(char* class_name) = 0;
		virtual LibraryForModule* get_library() = 0;
};

#endif