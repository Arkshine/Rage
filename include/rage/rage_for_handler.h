
#ifndef _INCLUDE_RAGE_FOR_HANDLER__H_
#define _INCLUDE_RAGE_FOR_HANDLER__H_

#include <function/function_for_handler.h>

class RageForHandler
{
	public:

		virtual FunctionForHandler* init() = 0;
		virtual void end() = 0;

		virtual REAL amx_ctof2(cell x) = 0;
		virtual cell amx_ftoc2(REAL x) = 0;
		virtual int private_to_index(const void *pdata) = 0;
		virtual void* index_to_private(int index) = 0;
		virtual entvars_t* index_to_entvar(int index) = 0;
		virtual int entvar_to_index(entvars_t *pev) = 0;
		virtual edict_t* entvar_to_edict(entvars_t *pev) = 0;

		virtual void write_console(char* format,...) = 0;
		virtual void write_console_ln(char* format,...) = 0;

		virtual void write_to_file(char* filename,char* format,...) = 0;
		virtual void write_to_file_ln(char* filename,char* format,...) = 0;

		virtual void add_error(char* format,...) = 0;
};

#endif
