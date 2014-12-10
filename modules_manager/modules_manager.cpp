
#include <modules_manager/modules_manager.h>
#include <util/util.h>
#include <global/global.h>
#include <dirent_os.h>
#include <rage/rage_for_module.h>

void ModulesManager::LoadedLibrary(LibraryForModule* library)
{
	for(CVector<ModuleForRage*>::iterator it = this->vector.begin(); it != this->vector.end(); it++)
		(*(it))->LoadedLibrary(library);
}

void ModulesManager::LoadedFunction(FunctionForModule* function)
{
	for(CVector<ModuleForRage*>::iterator it = this->vector.begin(); it != this->vector.end(); it++)
		(*(it))->LoadedFunction(function);
}

void ModulesManager::LoadedVirtualFunction(VirtualFunctionForModule* virtual_function)
{
	for(CVector<ModuleForRage*>::iterator it = this->vector.begin(); it != this->vector.end(); it++)
		(*(it))->LoadedVirtualFunction(virtual_function);
}

void ModulesManager::AmxxAttach(PFN_REQ_FNPTR reqFnptrFunc)
{
	for(CVector<ModuleForRage*>::iterator it = this->vector.begin(); it != this->vector.end(); it++)
		(*(it))->AMXX_Attach(reqFnptrFunc);
}

void ModulesManager::AmxxDetach()
{
	for(CVector<ModuleForRage*>::iterator it = this->vector.begin(); it != this->vector.end(); it++)
		(*(it))->AMXX_Detach();
}

void ModulesManager::PluginsLoaded()
{
	for(CVector<ModuleForRage*>::iterator it = this->vector.begin(); it != this->vector.end(); it++)
		(*(it))->AMXX_PluginsLoaded();
}

void ModulesManager::PluginsUnloading()
{
	for(CVector<ModuleForRage*>::iterator it = this->vector.begin(); it != this->vector.end(); it++)
		(*(it))->AMXX_PluginsUnloading();
}

void ModulesManager::PluginsUnloaded()
{
	for(CVector<ModuleForRage*>::iterator it = this->vector.begin(); it != this->vector.end(); it++)
		(*(it))->AMXX_PluginsUnloaded();
}

void ModulesManager::load_new_modules()
{
	static char modules_path[120];
	sprintf(modules_path,"%s/addons/rage/modules",Global::Mod);

	static char module_extension[30];
	sprintf(module_extension,".rm.%s",RAGE_LIBRARY_EXTENSION);
	int module_extension_len = strlen(module_extension);
	
	DIR* dir = opendir(modules_path);

	if(!dir)
	{
		Global::errorsManager.add_error("Unable to open modules directory");
		return;
	}

	dirent* dir_child;
	
	while( (dir_child = readdir(dir)) != NULL)
	{
		char* name_ = dir_child->d_name;
		int name_len = strlen(name_);

		if(name_len <= module_extension_len)
			continue;

		if(strcmp(module_extension,&name_[name_len - module_extension_len]))
			continue;

		char* module_name = new char[100];
		char* res = strncpy(module_name,name_,name_len - module_extension_len);
		module_name[name_len - module_extension_len] = 0;

		if(Global::modulesManager.get_by_label(module_name))
		{
			continue;
		}

		char module_path[200];
		sprintf(module_path,"%s/addons/rage/modules/%s.rm.%s",Global::Mod,module_name,RAGE_LIBRARY_EXTENSION);

		Library* library = create_library(module_path);

		if(library == NULL)
		{
			Global::errorsManager.add_error("Unable to add module %s as library",module_name);
			continue;
		}

		ModuleForRage* (*RageQuery)(RageForModule*) = (ModuleForRage* (*) (RageForModule*)) library->get_address_by_name("Rage_Query");

		if(!RageQuery)
		{
			Global::errorsManager.add_error("Entry point not found on module %s",module_name);
			continue;
		}

		ModuleForRage* module = RageQuery(Global::rage);

		if(library->get_address_by_name("Meta_Query"))
		{
			static char module_path_meta[100];
			sprintf(module_path_meta,"addons%crage%cmodules%c%s.rm.%s",RAGE_FILENAME_SEPARATOR,RAGE_FILENAME_SEPARATOR,RAGE_FILENAME_SEPARATOR,module_name,RAGE_LIBRARY_EXTENSION);
			META_ERRNO meta_result = (META_ERRNO) gpMetaUtilFuncs->pfnLoadPlugin(PLID,module_path_meta,PT_STARTUP,NULL);

			if(meta_result != ME_NOERROR)
			{
				Global::errorsManager.add_error("Unable to add module %s to metamod",module_name);
				continue;
			}
		}

		Global::modulesManager.add(module_name,module);
	}	
}
