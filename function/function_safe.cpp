
#include <function/function_safe.h>
#include <global/global.h>

void FunctionSafe::show_description()
{
	Util::WriteToConsole(", function '%s'",this->func_name);

	Util::WriteToConsole(", handler '%s'",this->handler->get_name());

	Library* library = this->library;
	
	if(library)
	{
		Util::WriteToConsole(", library: '%s' , offset: '0x%x'",library->get_name(),library->get_offset_of_address(this->original_address));
	}
	else
	{
		Util::WriteToConsole(", library: 'unknown' address: '0x%x'",this->original_address);
	}
}

char* FunctionSafe::get_name()
{
	return this->func_name;
}
