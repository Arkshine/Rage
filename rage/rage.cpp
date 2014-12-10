
#include <rage/rage.h>
#include <memory/memory.h>
#include <global/global.h>
#include <NEW_Util.h>
#include <config_parser/config_parser.h>
#include <modules_manager/modules_manager.h>
#include <util/util.h>

bool Rage::change_memory_protection(void* address,unsigned int size,unsigned long newProtection)
{
	return Memory::ChangeMemoryProtection(address,size,newProtection);	
}

bool Rage::change_memory_protection(void* address,unsigned int size,unsigned long newProtection,unsigned long & oldProtection)
{
	return Memory::ChangeMemoryProtection(address,size,newProtection,oldProtection);
}

FunctionForHandler* Rage::init()
{
	assert(Global::functionsManager.get_by_id(Global::CurrentFunctionID));

	Function* function = *Global::functionsManager.get_by_id(Global::CurrentFunctionID);

	Global::callStack.push(function);

	return function;
}

void Rage::end()
{
	Global::callStack.pop_discard();
}

REAL Rage::amx_ctof2(cell x)
{
	return amx_ctof2_(x);
}

cell Rage::amx_ftoc2(REAL x)
{
	return amx_ftoc2_(x);
}

int Rage::private_to_index(const void *pdata)
{
	return PrivateToIndex(pdata);
}

void* Rage::index_to_private(int index)
{
	return IndexToPrivate(index);
}

entvars_t* Rage::index_to_entvar(int index)
{
	return IndexToEntvar(index);
}

int Rage::entvar_to_index(entvars_t *pev)
{
	return EntvarToIndex(pev);
}

edict_t* Rage::entvar_to_edict(entvars_t *pev)
{
	return EntvarToEdict(pev);
}

cell AMX_NATIVE_CALL Rage::SetParam(AMX* amx,cell* params)
{
	Function* function = NULL;
	
	if(!Global::callStack.get(function))
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "rage_set_param called at an invalid point");
		return 0;
	}

	function->get_handler()->rage_set_param(amx,params);

	return 0;
}

LibraryForModule* Rage::insert_library(void* contained_address, char* name)
{
	Library* library = create_library(contained_address,name);

	if(!library)
		return NULL;

	Global::librariesManager.add(name,library);

	return library;
}

FunctionForModule* Rage::get_function(char* name)
{
	Function** function_ptr = Global::functionsManager.get_by_label(name);

	if(!function_ptr)
		return NULL;

	return *function_ptr;
}

VirtualFunctionForModule* Rage::get_virtual_function(char* name)
{
	VirtualFunction** virtual_function_ptr = Global::virtualFunctionsManager.get_by_label(name);

	if(!virtual_function_ptr)
		return NULL;

	return *virtual_function_ptr;
}

LibraryForModule* Rage::get_library(char* name)
{
	Library** library_ptr = Global::librariesManager.get_by_label(name);

	if(!library_ptr)
		return NULL;

	return *library_ptr;
}

void Rage::write_console(char* format,...)
{
	va_list argptr;
	va_start(argptr,format);
	static char msg[1000];
	vsprintf(msg,format,argptr);
	va_end(argptr);

	g_engfuncs.pfnServerPrint(msg);
}

void Rage::write_console_ln(char* format,...)
{
	va_list argptr;
	va_start(argptr,format);
	static char msg[1000];
	vsprintf(msg,format,argptr);
	va_end(argptr);

	g_engfuncs.pfnServerPrint(msg);
	g_engfuncs.pfnServerPrint("\n");
}

void Rage::write_to_file(char* filename,char* format,...)
{
	FILE* f = fopen(filename,"a+");
	
	if(!f)
	{
		Global::errorsManager.add_error("write_to_file failed to open file '%s'",filename);
		return;
	}

	va_list argptr;
	va_start(argptr,format);
	vfprintf(f,format,argptr);
	va_end(argptr);

	fclose(f);
}

void Rage::write_to_file_ln(char* filename,char* format,...)
{
	FILE* f = fopen(filename,"a+");
	
	if(!f)
	{
		Global::errorsManager.add_error("write_to_file_ln failed to open file '%s'",filename);
		return;
	}

	va_list argptr;
	va_start(argptr,format);
	vfprintf(f,format,argptr);
	va_end(argptr);

	fprintf(f,"\n");

	fclose(f);
}

void Rage::add_error(char* format,...)
{
	va_list argptr;
	va_start(argptr,format);
	static char error[1000];
	vsprintf(error,format,argptr);
	va_end(argptr);

	Global::errorsManager.add_error(error);
}

int Rage::get_pev()
{
	return Global::PEV;
}

int Rage::get_vtable_offset(char* classname)
{
	int* vtable_offset_ptr = Global::vtableOffsets.retrieve(classname);

	if(!vtable_offset_ptr)
		return -1;

	return *vtable_offset_ptr;
}

cell AMX_NATIVE_CALL Rage::GetFunction(AMX* amx,cell* params)
{
	int len;
	char *functionName = g_fn_GetAmxString(amx,params[1],0,&len);

	unsigned int id = Global::functionsManager.get_id_of(functionName);

	if(id == -1)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Function \"%s\" not found in rage",functionName);
	}

	return id;
}

cell AMX_NATIVE_CALL Rage::TryGetFunction(AMX* amx,cell* params)
{
	int len;
	char *functionName = g_fn_GetAmxString(amx,params[1],0,&len);

	return Global::functionsManager.get_id_of(functionName);
}

cell AMX_NATIVE_CALL Rage::CreateHook(AMX* amx,cell* params)
{
	unsigned int function_id = params[1];

	Function** function_ptr = Global::functionsManager.get_by_id(function_id);

	if(!function_ptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Invalid function %d provided to rage_create_hook",function_id);
		return -1;
	}

	Function* function = *function_ptr;

	int len;
	char *functionName = g_fn_GetAmxString(amx,params[2],0,&len);

	int id;
	int find = g_fn_AmxFindPublic(amx,functionName,&id);

	if(find == AMX_ERR_NOTFOUND)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Function not found in the plugin (be sure it's public) %s",functionName);
		return -1;
	}

	int phase = params[3];

	if(phase != !!phase)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Invalid phase");
		return -1;
	}

	return function->add_plugin_hook(amx,functionName,phase);


}

cell AMX_NATIVE_CALL Rage::RemoveHook(AMX* amx,cell* params)
{
	cell* hook_id = MF_GetAmxAddr(amx,params[1]);
	
	Hook* hook = Global::hook_id_to_func.find(*hook_id);

	if(!hook)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Unabled to find hook \"%d\" to remove",*hook_id);
		return 0;
	}

	Function* function = hook->function;
	
	if(!function->remove_plugin_hook(*hook_id,hook->phase))
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "'Unexpected' failure on removing the hook '%d'. Please contact the author",*hook_id);
		return 0;
	}

	*hook_id = -1;

	return 1;
}

cell AMX_NATIVE_CALL Rage::SetReturn(AMX* amx,cell* params)
{
	Function* function = NULL;
	
	if(!Global::callStack.get(function))
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "rage_set_return called at an invalid point");
		return 0;
	}

	function->get_handler()->rage_set_return(amx,params);

	return 0;
}

cell AMX_NATIVE_CALL Rage::GetReturn(AMX* amx,cell* params)
{
	Function* function = NULL;
	
	if(!Global::callStack.get(function))
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "rage_get_return called at an invalid point");
		return 0;
	}

	return function->get_handler()->rage_get_return(amx,params);
}

cell AMX_NATIVE_CALL Rage::Call(AMX* amx,cell* params)
{
	unsigned int function_id = params[1];

	Function** function_ptr = Global::functionsManager.get_by_id(function_id);

	if(!function_ptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Invalid function %d provided to rage_call",function_id);
		return -1;
	}

	Function* function = *function_ptr;

	params[1] = params[0]-1;
	params++;

	return function->get_handler()->rage_call(function,amx,params);
}

cell AMX_NATIVE_CALL Rage::GetFunctionFromClass(AMX* amx,cell* params)
{
	int len;
	char *func_name = g_fn_GetAmxString(amx,params[1],0,&len);

	VirtualFunction** virtual_function_ptr = Global::virtualFunctionsManager.get_by_label(func_name);
	
	if(!virtual_function_ptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Virtual function %s not registered",func_name);
		return -1;
	}

	VirtualFunction* virtual_function = *virtual_function_ptr;

	char* class_name = g_fn_GetAmxString(amx,params[2],0,&len);

	static char class_name_cp[50];
	strncpy(class_name_cp,class_name,49);

	edict_t *entity = CREATE_ENTITY();
	CALL_GAME_ENTITY(PLID,class_name,&entity->v);

	if(!entity->pvPrivateData)
	{
		REMOVE_ENTITY(entity);

		MF_LogError(amx, AMX_ERR_NATIVE,"Unable to create an entity of class '%s'",class_name);
		return -1;
	}

	int ret = virtual_function->create_get_id(entity->pvPrivateData,class_name_cp);
	
	REMOVE_ENTITY(entity);

	return ret;
}

cell AMX_NATIVE_CALL Rage::GetFunctionFromEntity(AMX* amx,cell* params)
{
	int len;
	char *func_name = g_fn_GetAmxString(amx,params[1],0,&len);

	VirtualFunction** virtual_function_ptr = Global::virtualFunctionsManager.get_by_label(func_name);
	
	if(!virtual_function_ptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Virtual function %s not registered",func_name);
		return -1;
	}

	VirtualFunction* virtual_function = *virtual_function_ptr;

	int entity = (int) params[2];

	void* object = IndexToPrivate(entity);

	if(!object)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Failed to get private data of entity '%d' for use with virtual function '%s'",entity,func_name);
		return -1;
	}

	return virtual_function->create_get_id(object);
}

cell AMX_NATIVE_CALL Rage::GetFunctionFromObject(AMX* amx,cell* params)
{
	int len;
	char *func_name = g_fn_GetAmxString(amx,params[1],0,&len);

	VirtualFunction** virtual_function_ptr = Global::virtualFunctionsManager.get_by_label(func_name);
	
	if(!virtual_function_ptr)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Virtual function %s not registered",func_name);
		return -1;
	}

	VirtualFunction* virtual_function = *virtual_function_ptr;

	void* object = (void*) params[2];

	return virtual_function->create_get_id(object);
}

AMX_NATIVE_INFO Rage::Exports[] =
{
	{"RageSetParam",&Rage::SetParam},
	{"RageGetFunction",&Rage::GetFunction},
	{"RageTryGetFunction",&Rage::TryGetFunction},
	{"RageCreateHook",&Rage::CreateHook},
	{"RageRemoveHook",&Rage::RemoveHook},
	{"RageGetReturn",&Rage::GetReturn},
	{"RageSetReturn",&Rage::SetReturn},
	{"RageCall",&Rage::Call},
	{"RageGetFunctionFromClass",&Rage::GetFunctionFromClass},
	{"RageGetFunctionFromEntity",&Rage::GetFunctionFromEntity},
	{"RageGetFunctionFromObject",&Rage::GetFunctionFromObject},
	{NULL, NULL}
};

void Rage::OnCommandRage()
{
	Command* command = NULL;

	if(CMD_ARGC() == 2)
	{
		const char* argument = CMD_ARGV(1); 
		Command** command_ptr = Global::commandsManager.get_by_label(const_cast<char*>(argument));

		if(command_ptr)
			command = *command_ptr;
	}

	if(!command)
	{
		command = *Global::commandsManager.get_by_label("rage");
	}

	command->run();
}

void Rage::OnMetaQuery()
{
	static bool queried = false;

	if(!queried)
	{
		queried = true;

		g_engfuncs.pfnGetGameDir(Global::Mod);

		parse_config();
		parse_new_vtables();

		Global::modulesManager.load_new_modules();
		Global::handlerCreatorManager.load_new_handler_creators();

		Global::commandsManager.load_commands();
		
		Global::librariesManager.load_libraries_query();
	}
}

void Rage::OnAmxxAttach(PFN_REQ_FNPTR reqFnptrFunc)
{
	static bool attached = false;

	if(!attached)
	{
		attached = true;

		Global::librariesManager.load_libraries_attach();

		g_engfuncs.pfnAddServerCommand("rage",&Rage::OnCommandRage);

		MF_AddNatives(Rage::Exports);
	}

	Global::modulesManager.AmxxAttach(reqFnptrFunc);
	Global::handlerCreatorManager.AmxxAttach(reqFnptrFunc);
}

void Rage::OnAmxxDetach()
{
	Global::modulesManager.AmxxDetach();
	Global::handlerManager.AmxxDetach();
}

void Rage::OnPluginsLoaded()
{
	NEW_Initialize(INDEXENT(0));

	Global::modulesManager.PluginsLoaded();
	Global::handlerManager.PluginsLoaded();
}

void Rage::OnPluginsUnloading()
{
	Global::modulesManager.PluginsUnloading();
	Global::handlerManager.PluginsUnloading();
}

void Rage::OnPluginsUnloaded()
{
	Global::handlerManager.PluginsUnloaded();
	Global::handlerManager.PluginsUnloaded();

	Global::functionsManager.clear_plugin_hooks();
	Global::hook_id_to_func.clear();

	// Check for new files
	{
		parse_new_vtables();

		Global::modulesManager.load_new_modules();
		Global::handlerCreatorManager.load_new_handler_creators();

		Global::librariesManager.parse_new_functions();
	}
}

extern "C" void __cxa_pure_virtual() 
{
   abort();
}

void __cxa_guard_acquire()
{

}

void __cxa_guard_release()
{

} 
