
#ifndef _INCLUDE_ERROR_MANAGER_H_
#define _INCLUDE_ERROR_MANAGER_H_

#include <CVector.h>

class ErrorsManager
{
	CVector<char*> errors;

	public:

		void add_error(char* format,...);
		void list();
};

#endif