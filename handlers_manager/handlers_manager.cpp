
#include <handlers_manager/handlers_manager.h>

void HandlerManager::AmxxDetach()
{
	CVector<HandlerForRage*>::iterator it = this->vector.begin();

	while(it != this->vector.end())
	{
		HandlerForRage* object = *(it++);

		object->AMXX_Detach();
	}
}

void HandlerManager::PluginsLoaded()
{
	CVector<HandlerForRage*>::iterator it = this->vector.begin();

	while(it != this->vector.end())
	{
		HandlerForRage* object = *(it++);

		object->AMXX_PluginsLoaded();
	}
}

void HandlerManager::PluginsUnloading()
{
	CVector<HandlerForRage*>::iterator it = this->vector.begin();

	while(it != this->vector.end())
	{
		HandlerForRage* object = *(it++);
		
		object->AMXX_PluginsUnloading();
	}
}

void HandlerManager::PluginsUnloaded()
{
	CVector<HandlerForRage*>::iterator it = this->vector.begin();

	while(it != this->vector.end())
	{
		HandlerForRage* object = *(it++);
		
		object->AMXX_PluginsUnloaded();
	}
}
