
#ifndef _INCLUDE_HANDLER_CREATOR_MANAGER_H_
#define _INCLUDE_HANDLER_CREATOR_MANAGER_H_

#include <manager/manager.h>

#include <handler_creator/handler_creator_for_rage.h>

class HandlerCreatorManager : public Manager<HandlerCreatorForRage*>
{
	public:
		void AmxxAttach(PFN_REQ_FNPTR reqFnptrFunc);

		static void load_new_handler_creators();
};




#endif

