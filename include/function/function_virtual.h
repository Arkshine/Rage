
#ifndef __FUNCTION_VIRTUAL_H__
#define __FUNCTION_VIRTUAL_H__

#include <function/function.h>

class FunctionVirtual : public Function
{
	
	private:

		char class_name[50];
		char* func_name;

	public:
	
		FunctionVirtual(void* address, void* managed_address, HandlerForRage* handler,char* func_name,char* class_name,Library* library) : Function(address,managed_address,handler,library) , func_name(func_name)
		{
			if(class_name)
			{
				strncpy(this->class_name,class_name,49);
			}
			else
			{
				this->class_name[0] = 0;
			}
		}

		void pre_call(){}
		void post_call(){}

		void show_description()
		{
			Util::WriteToConsole(", virtual function '%s'",this->func_name);

			Util::WriteToConsole(", handler '%s'",this->handler->get_name());

			if(this->class_name)
			{
				Util::WriteToConsole(", classname '%s'",this->class_name);
			}

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

		char* get_name()
		{
			return this->func_name;
		}
};

#endif