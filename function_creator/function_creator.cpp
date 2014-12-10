
#include <function_creator/function_creator.h>
#include <global/global.h>

Function* FunctionCreator::create_function(char* func_name,void* address,HandlerForRage* handler,Library* library)
{
	unsigned int next_id = Global::functionsManager.get_next_id();
	Function* function = Global::patcher.do_patch(address,handler,next_id,func_name,library);
	Global::functionsManager.add(func_name,function);

	Global::modulesManager.LoadedFunction(function);

	return function;
}

unsigned int FunctionCreator::create_virtual_function(void* address,void** address_in_table,HandlerForRage* handler,char* func_name,char* class_name,Library* library)
{
	int* id_ptr = virtual_functions_address_in_table_to_id.find((int)address_in_table);
	
	if(id_ptr)
	{
		return *id_ptr;
	}

	unsigned int next_id = Global::functionsManager.get_next_id();
	Function* function = Global::patcher.do_patch_virtual(address,address_in_table,handler,next_id,func_name,class_name,library);
	Global::functionsManager.add(function);

	virtual_functions_address_in_table_to_id.add((int)address_in_table,next_id);

	return next_id;
}
