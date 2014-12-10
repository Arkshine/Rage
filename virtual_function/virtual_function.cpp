
#include <virtual_function/virtual_function.h>
#include <global/global.h>

VirtualFunction::VirtualFunction(char* func_name,HandlerCreatorForRage* handler_creator,int vtable_offset,int offset,Library* library) : func_name(func_name), handler_creator(handler_creator) , vtable_offset(vtable_offset), offset(offset), library(library)
{

}

unsigned int VirtualFunction::create_get_id(void* object)
{
	return this->create_get_id(object,NULL);
}

unsigned int VirtualFunction::create_get_id(void* object,char* class_name)
{
	void **vtable = *((void***)(((char*)object)+this->vtable_offset));
	
	void** address_in_table = &vtable[this->offset];

	void* address = *address_in_table;

	HandlerForRage* handler = handler_creator->create();
	Global::handlerManager.add(handler);

	return Global::functionCreator.create_virtual_function(address,address_in_table,handler,this->func_name,class_name,this->library);
}

FunctionForModule* VirtualFunction::create_with_object(void* object)
{
	return *Global::functionsManager.get_by_id(this->create_get_id(object));
}

FunctionForModule* VirtualFunction::create_with_class(char* class_name)
{
	edict_t *entity = CREATE_ENTITY();
	CALL_GAME_ENTITY(PLID,class_name,&entity->v);

	if(!entity->pvPrivateData)
	{
		REMOVE_ENTITY(entity);
		return NULL;
	}

	FunctionForModule* function = *Global::functionsManager.get_by_id(this->create_get_id(entity->pvPrivateData,class_name));
	REMOVE_ENTITY(entity);
	return function;
}

char* VirtualFunction::get_name()
{
	return this->func_name;
}

Library* VirtualFunction::get_library()
{
	return this->library;
}