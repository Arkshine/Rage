
#include <handler_creator_manager/handler_creator_manager.h>

#include <global/global.h>

#include <dirent_os.h>
#include <util/util.h>
#include <library/library.h>

#include <handler/handler_for_rage.h>

void HandlerCreatorManager::AmxxAttach(PFN_REQ_FNPTR reqFnptrFunc)
{
	CVector<HandlerCreatorForRage*>::iterator it = this->vector.begin();

	while(it != this->vector.end())
	{
		HandlerCreatorForRage* object = *(it++);

		object->AMXX_Attach(reqFnptrFunc);
	}
}

void HandlerCreatorManager::load_new_handler_creators()
{
	static char handlers_path[120];
	sprintf(handlers_path,"%s/addons/rage/handlers",Global::Mod);

	static char handler_extension[30];
	sprintf(handler_extension,".rh.%s",RAGE_LIBRARY_EXTENSION);
	int handler_extension_len = strlen(handler_extension);
	
	DIR* dir = opendir(handlers_path);

	if(!dir)
	{
		Global::errorsManager.add_error("Unable to open handlers directory");
		return;
	}

	dirent* dir_child;
	
	while( (dir_child = readdir(dir)) != NULL)
	{
		char* name_ = dir_child->d_name;
		int name_len = strlen(name_);

		if(name_len <= handler_extension_len)
			continue;

		if(strcmp(handler_extension,&name_[name_len - handler_extension_len]))
			continue;

		char* handler_name = new char[300];
		char* res = strncpy(handler_name,name_,name_len - handler_extension_len);
		handler_name[name_len - handler_extension_len] = 0;

		if(Global::handlerCreatorManager.get_by_label(handler_name))
		{
			continue;
		}

		char handler_path[300];
		sprintf(handler_path,"%s/addons/rage/handlers/%s.rh.%s",Global::Mod,handler_name,RAGE_LIBRARY_EXTENSION);

		Library* library = create_library(handler_path);

		if(library == NULL)
		{
			Global::errorsManager.add_error("Unable to add handler %s as library",handler_name);
			continue;
		}

		HandlerCreatorForRage* (*RageQuery)(RageForHandler*) = (HandlerCreatorForRage* (*) (RageForHandler*)) library->get_address_by_name("Rage_Query");

		if(!RageQuery)
		{
			Global::errorsManager.add_error("Entry point not found on handler %s",handler_name);
			continue;
		}

		HandlerCreatorForRage* handler_creator = RageQuery(Global::rage);

		handler_creator->set_filename(handler_name);

		if(library->get_address_by_name("Meta_Query"))
		{
			static char module_path_meta[300];
			sprintf(module_path_meta,"addons%crage%chandlers%c%s.rh.%s",RAGE_FILENAME_SEPARATOR,RAGE_FILENAME_SEPARATOR,RAGE_FILENAME_SEPARATOR,handler_name,RAGE_LIBRARY_EXTENSION);
			META_ERRNO meta_result = (META_ERRNO) gpMetaUtilFuncs->pfnLoadPlugin(PLID,module_path_meta,PT_STARTUP,NULL);

			if(meta_result != ME_NOERROR)
			{
				Global::errorsManager.add_error("Unable to add handler %s to metamod",handler_name);
				continue;
			}
		}

		Global::handlerCreatorManager.add(handler_name,handler_creator);
	}	
}