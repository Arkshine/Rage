
#include <global/global.h>
#include <libraries_manager/libraries_manager.h>
#include "amxxmodule.h"
#include <config_parser/config_parser.h>

void LibrariesManager::load_libraries_query()
{
	Global::librariesManager.add("engine",create_library((void*)gpGlobals,"engine"));
}

void LibrariesManager::load_libraries_attach()
{
	Global::librariesManager.add("metamod",create_library((void*)gpMetaGlobals,"metamod"));

	Library* mod_library = create_library((void*)MNEW_OnFreeEntPrivateData,"mod");

	if(!mod_library)
	{
		mod_library = create_library((void*)MDLL_Spawn,"mod");
	}

	if(!mod_library)
	{
		Global::errorsManager.add_error("Unable to add mod to libraries");
	}

	Global::librariesManager.add("mod",mod_library);
}

bool LibrariesManager::add(char* label,Library* library)
{
	if(this->get_by_label(label))
		return false;
	
	bool added = Manager<Library*>::add(label,library);

	if(!added)
		return false;

	Global::modulesManager.LoadedLibrary(library);

	parse_functions(label,library);

	return true;
}

Library* LibrariesManager::get_library_from_address(void *address)
{
	Library* fake_library = create_library(address,NULL);

	CVector<Library*> libraries = this->get_vector();

	for(unsigned int i=0;i<libraries.size();i++)
	{
		Library* library = libraries[i];

		if(library->get_base_address() == fake_library->get_base_address())
		{
			delete fake_library;
			return library;
		}
	}

	delete fake_library;
	return NULL;
}

void LibrariesManager::parse_new_functions()
{
	CVector<Library*> libraries = this->get_vector();

	for(unsigned int i=0;i<libraries.size();i++)
	{
		Library* library = libraries[i];

		parse_functions(library->get_name(),library);
	}
}


