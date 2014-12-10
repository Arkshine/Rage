
#ifndef _INCLUDE_FUNCTION_INCOMPLETE_H_
#define _INCLUDE_FUNCTION_INCOMPLETE_H_

#include <handler/handler_for_rage.h>
#include <function/function_for_module.h>
#include <global/global.h>
#include <function_incomplete/function_incomplete_for_module.h>

class FunctionIncomplete : public FunctionIncompleteForModule
{
	private:

		char* func_name;
		HandlerForRage* handler;
		Library* library;

	public:
		
		FunctionIncomplete(char* func_name,HandlerForRage* handler,Library* library) : func_name(func_name) , handler(handler), library(library)
		{

		}

		FunctionForModule* finish(void* address)
		{
			return Global::functionCreator.create_function(func_name,address,handler,library);
		}

		char* get_name()
		{
			return this->func_name;
		}

		Library* get_library()
		{
			return this->library;
		}
};

#endif

