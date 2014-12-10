
#ifndef _INCLUDE_HANDLER_CREATOR_FOR_RAGE__H_
#define _INCLUDE_HANDLER_CREATOR_FOR_RAGE__H_

#include <handler/handler_for_rage.h>

class HandlerCreatorForRage
{
	public:
	
		virtual HandlerForRage* create() = 0;
		virtual int AMXX_Attach(PFN_REQ_FNPTR reqFnptrFunc) = 0;

		virtual void set_filename(char* filename) = 0;

		virtual char* get_name() = 0;
		virtual char* get_author() = 0;
		virtual char* get_version() = 0;
};

#endif
