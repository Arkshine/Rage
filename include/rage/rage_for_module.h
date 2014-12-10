
#ifndef _INCLUDE_RAGE_FOR_MODULE__H_
#define _INCLUDE_RAGE_FOR_MODULE__H_

#include <library/library_for_module.h>
#include <function/function_for_module.h>
#include <virtual_function/virtual_function_for_module.h>

class RageForModule
{
	public:

		virtual bool change_memory_protection(void* address,unsigned int size,unsigned long newProtection) = 0;
		virtual bool change_memory_protection(void* address,unsigned int size,unsigned long newProtection,unsigned long & oldProtection) = 0;

		virtual REAL amx_ctof2(cell x) = 0;
		virtual cell amx_ftoc2(REAL x) = 0;
		virtual int private_to_index(const void *pdata) = 0;
		virtual void* index_to_private(int index) = 0;
		virtual entvars_t* index_to_entvar(int index) = 0;
		virtual int entvar_to_index(entvars_t *pev) = 0;
		virtual edict_t* entvar_to_edict(entvars_t *pev) = 0;

		virtual LibraryForModule* insert_library(void* contained_address, char* name) = 0;
		virtual FunctionForModule* get_function(char* name) = 0;
		virtual VirtualFunctionForModule* get_virtual_function(char* name) = 0;
		virtual LibraryForModule* get_library(char* name) = 0;

		virtual void write_console(char* format,...) = 0;
		virtual void write_console_ln(char* format,...) = 0;

		virtual void write_to_file(char* filename,char* format,...) = 0;
		virtual void write_to_file_ln(char* filename,char* format,...) = 0;

		virtual void add_error(char* format,...) = 0;

		virtual int get_pev() = 0;
		virtual int get_vtable_offset(char* classname) = 0;
};

#endif
