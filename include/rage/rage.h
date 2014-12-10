
#ifndef _INCLUDE_RAGE__H_
#define _INCLUDE_RAGE__H_

#include "amxxmodule.h"
#include <rage/rage_for_module.h>
#include <rage/rage_for_handler.h>
#include <library/library_for_module.h>

class Rage : public RageForModule, public RageForHandler
{
	public:
	
		static cell AMX_NATIVE_CALL SetParam(AMX* amx,cell* params);
		static cell AMX_NATIVE_CALL TryGetFunction(AMX* amx,cell* params);
		static cell AMX_NATIVE_CALL CreateHook(AMX* amx,cell* params);
		static cell AMX_NATIVE_CALL GetFunction(AMX* amx,cell* params);
		static cell AMX_NATIVE_CALL RemoveHook(AMX* amx,cell* params);
		static cell AMX_NATIVE_CALL SetReturn(AMX* amx,cell* params);
		static cell AMX_NATIVE_CALL GetReturn(AMX* amx,cell* params);
		static cell AMX_NATIVE_CALL Call(AMX* amx,cell* params);
		static cell AMX_NATIVE_CALL GetFunctionFromClass(AMX* amx,cell* params);
		static cell AMX_NATIVE_CALL GetFunctionFromEntity(AMX* amx,cell* params);
		static cell AMX_NATIVE_CALL GetFunctionFromObject(AMX* amx,cell* params);

		static AMX_NATIVE_INFO Exports[];

		static void OnCommandRage();
		static void OnMetaQuery();
		static void OnAmxxAttach(PFN_REQ_FNPTR reqFnptrFunc);
		static void OnAmxxDetach();
		static void OnPluginsLoaded();
		static void OnPluginsUnloading();
		static void OnPluginsUnloaded();

		/* For both */
		REAL amx_ctof2(cell x);
		cell amx_ftoc2(REAL x);
		int private_to_index(const void *pdata);
		void* index_to_private(int index);
		entvars_t* index_to_entvar(int index);
		int entvar_to_index(entvars_t *pev);
		edict_t* entvar_to_edict(entvars_t *pev);

		void write_console(char* format,...);
		void write_console_ln(char* format,...);

		void write_to_file(char* filename,char* format,...);
		void write_to_file_ln(char* filename,char* format,...);

		void add_error(char* format,...);

		/* For Modules */
		bool change_memory_protection(void* address,unsigned int size,unsigned long newProtection);
		bool change_memory_protection(void* address,unsigned int size,unsigned long newProtection,unsigned long & oldProtection);

		LibraryForModule* insert_library(void* contained_address, char* name);
		FunctionForModule* get_function(char* name);
		VirtualFunctionForModule* get_virtual_function(char* name);
		LibraryForModule* get_library(char* name);

		int get_pev();
		int get_vtable_offset(char* classname);

		/* For Handlers */
		FunctionForHandler* init();
		void end();
};

#endif