
#ifndef _INCLUDE_COMMAND_H_
#define _INCLUDE_COMMAND_H_

class Command
{
		char* name;

	public:
		
		virtual void run() = 0;
		virtual void show_description() = 0;
		
		Command(char* name) : name(name)
		{

		}

		char* get_name()
		{
			return this->name;
		}
};

#endif