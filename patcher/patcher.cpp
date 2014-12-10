
#include <patcher/patcher.h>
#include <global/global.h>
#include <function/function_virtual.h>
#include <function/function_safe.h>

unsigned char PreJumpBase[] = {0x66,0xc7,0x5,0x00,0x00,0x00,0x00,0x00,0x0,0xe9,0x00,0x00,0x00,0x00};
unsigned int PreJumpSize = sizeof PreJumpBase;

unsigned int PreJumpIDAddressPosition = 3;
unsigned int PreJumpIDValuePosition = 7;
unsigned int PreJumpIDHookAddressPosition = 10;

Function* Patcher::do_patch_safe(void* address,HandlerForRage* handler,unsigned int id, char* func_name,Library* library)
{
	unsigned char* preJump = (unsigned char*) malloc(PreJumpSize);
	
	Memory::ChangeMemoryProtection(preJump,PreJumpSize,PAGE_EXECUTE_READWRITE);

	memcpy((void*)preJump,PreJumpBase,PreJumpSize);

	*((long*)(&preJump[PreJumpIDAddressPosition])) = (long) &Global::CurrentFunctionID;
	*((unsigned short int*)(&preJump[PreJumpIDValuePosition])) = id;

	*((long*)(&preJump[PreJumpIDHookAddressPosition])) = (char*) handler->get_gate_address() - (char*) preJump - PreJumpSize;

	unsigned char* patched_header = new unsigned char[Global::JumpSize];
	unsigned char* original_header = new unsigned char[Global::JumpSize];

	patched_header[0] = 0xE9;
	*((long*)(&patched_header[1])) = (char*)preJump - (char*)address - 5;
	
	memcpy((void*)original_header,address,Global::JumpSize);

	FunctionSafe* function =  new FunctionSafe(address,address,handler,original_header,patched_header,func_name,library);

	// Initiate hooking
	function->post_call();

	return function;
}

Function* Patcher::do_patch(void* address,HandlerForRage* handler,unsigned int id,char* func_name,Library* library)
{
	return this->do_patch_safe(address,handler,id,func_name,library);
}

Function* Patcher::do_patch_virtual(void* address,void** address_in_table,HandlerForRage* handler,unsigned int id,char* func_name,char* class_name,Library* library)
{
	unsigned char* preJump = (unsigned char*) malloc(PreJumpSize);
	
	Memory::ChangeMemoryProtection(preJump,PreJumpSize,PAGE_EXECUTE_READWRITE);

	memcpy((void*)preJump,PreJumpBase,PreJumpSize);

	*((long*)(&preJump[PreJumpIDAddressPosition])) = (long) &Global::CurrentFunctionID;
	*((unsigned short int*)(&preJump[PreJumpIDValuePosition])) = id;

	*((long*)(&preJump[PreJumpIDHookAddressPosition])) = (char*) handler->get_gate_address() - (char*) preJump - PreJumpSize;

	{
		unsigned long oldProtection;
		Memory::ChangeMemoryProtection(address_in_table,sizeof(void*),PAGE_READWRITE,oldProtection);
	
		*address_in_table = (void*) preJump;

		Memory::ChangeMemoryProtection(address_in_table,sizeof(void*),oldProtection);
	}

	FunctionVirtual* function = new FunctionVirtual(address,(void*)preJump,handler,func_name,class_name,library);

	return function;
}
