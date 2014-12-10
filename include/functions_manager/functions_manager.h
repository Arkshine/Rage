
#ifndef _INCLUDE_FUNCTIONS_MANAGER_H_
#define _INCLUDE_FUNCTIONS_MANAGER_H_

#include <function/function.h>
#include <manager/manager.h>

class FunctionsManager : public Manager<Function*>
{
	public:

		unsigned int get_next_id()
		{
			return this->vector.size();
		}

		void list()
		{
			Util::WriteToConsole("\n");

			CVector<Function*> functions = this->get_vector();

			for(unsigned int i=0;i<functions.size();i++)
			{
				Util::WriteToConsole("\tid: %d ",i);
				functions[i]->show_description();
				Util::WriteToConsole("\n");
			}

			Util::WriteToConsole("\n");
		}

		void clear_plugin_hooks()
		{
			CVector<Function*>::iterator current = this->vector.begin();

			while(current != this->vector.end())
			{
				(*(current++))->clear_plugin_hooks();
			}
		}
};

#endif