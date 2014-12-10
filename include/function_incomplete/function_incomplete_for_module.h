
#ifndef _INCLUDE_FUNCTION_INCOMPLETE_FOR_MODULE_H_
#define _INCLUDE_FUNCTION_INCOMPLETE_FOR_MODULE_H_

#include <function/function_for_module.h>

class FunctionIncompleteForModule
{
	public:
		
		virtual FunctionForModule* finish(void* address) = 0;
		virtual char* get_name() = 0;
		virtual LibraryForModule* get_library() = 0;
};

#endif

