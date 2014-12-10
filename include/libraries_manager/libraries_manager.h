
#ifndef _INCLUDE_LIBRARIES_MANAGER_H_
#define _INCLUDE_LIBRARIES_MANAGER_H_

#include <library/library.h>
#include <manager/manager.h>
#include <util/util.h>

class LibrariesManager : public Manager<Library*>
{
	public:

		bool add(char* label,Library* library);

		Library* get_library_from_address(void *address);

		void parse_new_functions();

		static void load_libraries_attach();
		static void load_libraries_query();
};



#endif