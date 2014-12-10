
#ifndef _INCLUDE_HANDLERS_MANAGER_H_
#define _INCLUDE_HANDLERS_MANAGER_H_

#include "amxxmodule.h"

#include <handler/handler_for_rage.h>
#include <manager/manager.h>

class HandlerManager : public Manager<HandlerForRage*>
{
	public:

		void AmxxDetach();
		void PluginsLoaded();
		void PluginsUnloading();
		void PluginsUnloaded();
};

#endif