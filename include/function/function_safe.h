
#ifndef __FUNCTION_SAFE_H__
#define __FUNCTION_SAFE_H__

#include <function/function.h>
#include <memory/memory.h>

const int PatchSize = 5;

class FunctionSafe : public Function
{
	unsigned char* original_header;
	unsigned char* patched_header;
	char* func_name;

	public:
	
		FunctionSafe(void* address, void* managed_address, HandlerForRage* handler, unsigned char* original_header,unsigned char* patched_header,char* func_name, Library* library) : Function(address,managed_address,handler,library) , original_header(original_header), patched_header(patched_header), func_name(func_name)
		{

		}

		void pre_call()
		{
			Memory::ChangeMemoryProtection(this->original_address,PatchSize,PAGE_EXECUTE_READWRITE);
			memcpy(this->original_address,(void*)original_header,PatchSize);
			Memory::ChangeMemoryProtection(this->original_address,PatchSize,PAGE_EXECUTE_READ);
		}

		void post_call()
		{
			Memory::ChangeMemoryProtection(this->original_address,PatchSize,PAGE_EXECUTE_READWRITE);
			memcpy(this->original_address,(void*)patched_header,PatchSize);
			Memory::ChangeMemoryProtection(this->original_address,PatchSize,PAGE_EXECUTE_READ);
		}

		void show_description();
		char* get_name();
};

#endif