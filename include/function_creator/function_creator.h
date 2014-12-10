
#ifndef __FUNCTION_CREATOR_H__
#define __FUNCTION_CREATOR_H__

#include <handler/handler_for_rage.h>
#include <trie/trie.h>
#include <function/function.h>

class FunctionCreator
{
	private:
		
		Trie<int> virtual_functions_address_in_table_to_id;

	public:
	
		Function* create_function(char* func_name,void* address,HandlerForRage* handler,Library* library);
		unsigned int create_virtual_function(void* address,void** address_in_table,HandlerForRage* handler,char* class_name,char* func_name,Library* library);
};

#endif