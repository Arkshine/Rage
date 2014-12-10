
#include <function/function.h>
#include <global/global.h>

Function::Function(void* original_address,void* managed_address,HandlerForRage* handler, Library* library) : original_address(original_address) , managed_address(managed_address), handler(handler), library(library)
{
	
}

void* Function::get_original_address()
{
	return this->original_address;
}

void* Function::get_managed_address()
{
	return this->managed_address;
}

int Function::add_plugin_hook(AMX* amx,const char* function_name,int phase)
{
	assert(phase == !!phase);

	int hook_id = this->handler->create_plugin_hook(amx,function_name);
	
	hooks[phase].push_back(hook_id);

	Hook hook = 
	{
		this,
		phase
	};

	Global::hook_id_to_func.add(hook_id,hook);

	return hook_id;
}

HandlerForRage* Function::get_handler()
{
	return this->handler;
}

void Function::clear_plugin_hooks()
{
	this->hooks[0].clear();
	this->hooks[1].clear();
}

bool Function::remove_plugin_hook(int hook_id,int phase)
{
	assert(phase == !!phase);

	CVector<int>::iterator it = this->hooks[phase].begin();

	while(it != this->hooks[phase].end())
	{
		if(*it == hook_id)
		{
			this->hooks[phase].erase(it);
			Global::hook_id_to_func.remove(hook_id);
			return true;
		}

		it++;
	}

	return false;
}

CVector<int>* Function::get_plugin_hooks()
{
	return this->hooks;
}

void Function::add_module_hook(void* address,RageHookPhase rage_hook_phase)
{
	this->hooks_modules[(unsigned int)rage_hook_phase].push_back(address);	
}

bool Function::remove_module_hook(void* address,RageHookPhase rage_hook_phase)
{
	CVector<void*>::iterator it = this->hooks_modules[(unsigned int)rage_hook_phase].begin();

	for(;it != this->hooks_modules[(unsigned int)rage_hook_phase].end();it++)
	{
		if(address == *it)
		{
			this->hooks_modules[(unsigned int)rage_hook_phase].erase(it);
			return true;
		}
	}

	return false;
}

CVector<void*>* Function::get_module_hooks()
{
	return this->hooks_modules;
}

Library* Function::get_library()
{
	return this->library;
}