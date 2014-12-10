
#include <config_parser/config_parser.h>
#include <global/global.h>

#include <parser/parser.h>
#include <parser/parser_node_type.h>
#include <parser/node_types/parser_node_array.h>
#include <parser/node_types/parser_node_num.h>
#include <parser/node_types/parser_node_string.h>
#include <parser/node_types/parser_node_labeled_array.h>
#include <parser/node_types/parser_node_labeled_scalar.h>

#include <util/util.h>

#include <function_incomplete/function_incomplete.h>
#include <function_incomplete/function_incomplete_for_module.h>

void parser_mod_file(char* file)
{
	ParserNode* root = parse(file);

	if(!root)
	{
		return;
	}

	if(root->get_type() != ParserNodeTypeLabeledArray)
	{
		Global::errorsManager.add_error("The file for the configuration of mod is correctly formated but has an unexpected structure");
		return;
	}

	ParserNodeArray* root_array = static_cast<ParserNodeArray*>(static_cast<ParserNodeLabeledArray*>(root)->getNodeValue());

	{
		ParserNode* alias = root_array->getLabeledNode("alias");

		if(alias)
		{
			if(alias->get_type() != ParserNodeTypeLabeledScalar)
			{
				Global::errorsManager.add_error("The file for the configuration of mod as a ALIAS entry with an unexpected structure");
				return;
			}

			ParserNode* alias_scalar = static_cast<ParserNodeLabeledScalar*>(alias)->getNodeValue();

			if(alias_scalar->get_type() != ParserNodeTypeString)
			{
				Global::errorsManager.add_error("The file for the configuration of mod as a ALIAS entry with an unexpected structure");
				return;
			}

			ParserNodeString* alias_string = static_cast<ParserNodeString*>(alias_scalar);

			Global::Alias = alias_string->get_str();

			static char mod_config_path[120];
			sprintf(mod_config_path,"%s/addons/rage/config/mod/%s",Global::Mod,alias_string->get_str());
			return parser_mod_file(mod_config_path);
		}
	}

	{
		ParserNode* pev = root_array->getLabeledNode("pev");

		if(!pev)
		{
			Global::errorsManager.add_error("The file for the configuration of mod doesn't have a PEV entry");
			return;
		}

		if(pev->get_type() != ParserNodeTypeLabeledArray)
		{
			Global::errorsManager.add_error("The file for the configuration of mod as a PEV entry with an unexpected structure");
			return;
		}

		ParserNodeArray* pev_array = static_cast<ParserNodeArray*>(static_cast<ParserNodeLabeledArray*>(pev)->getNodeValue());


		ParserNode* pev_windows = pev_array->getLabeledNode(Global::OS);

		if(!pev_windows)
		{
			Global::errorsManager.add_error("The file for the configuration of mod doesn't have a PEV entry for your OS");
			return;
		}

		if(pev_windows->get_type() != ParserNodeTypeLabeledScalar)
		{
			Global::errorsManager.add_error("The file for the configuration of mod has a PEV entry for your OS with an invalid structure");
		}

		ParserNode* pev_windows_scalar = static_cast<ParserNodeArray*>(static_cast<ParserNodeLabeledArray*>(pev_windows)->getNodeValue());

		if(pev_windows_scalar->get_type() != ParserNodeTypeNum)
		{
			Global::errorsManager.add_error("The file for the configuration of mod has a PEV entry for your OS with an invalid structure");
		}

		ParserNodeNum* pev_windows_num = static_cast<ParserNodeNum*>(pev_windows_scalar);

		Global::PEV = pev_windows_num->get_num();
	}
}

void parse_mod_config()
{
	static char mod_config_path[120];
	sprintf(mod_config_path,"%s/addons/rage/config/mod/%s",Global::Mod,Global::Mod);

	return parser_mod_file(mod_config_path);
}

void parse_config()
{
	parse_mod_config();
}

#include <dirent_os.h>

void parse_function(Library* library,char* path,char* name)
{
	ParserNode* root = parse(path);

	if(!root)
	{
		return;
	}

	if(root->get_type() != ParserNodeTypeLabeledArray)
	{
		Global::errorsManager.add_error("The file for the function '%s' has an invalid structure",name);
		return;
	}

	ParserNodeLabeledArray* root_labeled_array = static_cast<ParserNodeLabeledArray*>(root);

	char* func_name = root_labeled_array->getNodeLabel()->get_str();

	Function** function_ptr = Global::functionsManager.get_by_label(func_name);

	if(function_ptr)
	{
		return;
	}

	ParserNodeArray* root_array = static_cast<ParserNodeArray*>(root_labeled_array->getNodeValue());
	
	ParserNode* handler_node = root_array->getLabeledNode("handler");

	if(!handler_node)
	{
		Global::errorsManager.add_error("The file for the function '%s' doesn't have a 'handler' entry",name);
		return;
	}

	if(handler_node->get_type() != ParserNodeTypeLabeledScalar)
	{
		Global::errorsManager.add_error("The file for the function '%s' has the 'handler' entry with an invalid structure",name);
	}

	ParserNode* handler_value_scalar = static_cast<ParserNodeLabeledScalar*>(handler_node)->getNodeValue();

	if(handler_value_scalar->get_type() != ParserNodeTypeString)
	{
		Global::errorsManager.add_error("The file for the function '%s' has the 'handler' entry with an invalid structure",name);
	}

	ParserNodeString* handler_value_string = static_cast<ParserNodeString*>(handler_value_scalar);

	char* handler_name = handler_value_string->get_str();

	HandlerCreatorForRage** handler_creator_ptr = Global::handlerCreatorManager.get_by_label(handler_name);

	if(!handler_creator_ptr)
	{
		Global::errorsManager.add_error("Function '%s' is requesting handler '%s' but it isn't registered",name,handler_name);
		return;
	}

	HandlerCreatorForRage* handler_creator = *handler_creator_ptr;

	ParserNode* identifiers = root_array->getLabeledNode("identifiers");

	if(!identifiers)
	{
		Global::errorsManager.add_error("Function '%s' doesn't have an 'identifiers' entry",name);
		return;
	}

	if(identifiers->get_type() != ParserNodeTypeLabeledArray)
	{
		Global::errorsManager.add_error("Function '%s' has the 'identifiers' entry with an invalid structure",name);
		return;
	}
	
	if(!strcmp(library->get_name(),"mod"))
	{
		ParserNodeArray* identifiers_array = static_cast<ParserNodeArray*>(static_cast<ParserNodeLabeledArray*>(identifiers)->getNodeValue());

		if(Global::Alias)
			identifiers = identifiers_array->getLabeledNode(Global::Alias);
		else
			identifiers = identifiers_array->getLabeledNode(Global::Mod);
		
		
		if(!identifiers)
		{
			Global::errorsManager.add_error("Function '%s' doesn't have identifiers for your mod",name);
			return;
		}
	}

	if(identifiers->get_type() != ParserNodeTypeLabeledArray)
	{
		Global::errorsManager.add_error("Function '%s' identifiers for your system has an invalid structure",name);
		return;
	}

	ParserNodeArray* identifiers_array = static_cast<ParserNodeArray*>(static_cast<ParserNodeLabeledArray*>(identifiers)->getNodeValue());

	ParserNode* identifiers_os = identifiers_array->getLabeledNode(Global::OS);

	if(!identifiers_os)
	{
		Global::errorsManager.add_error("Function '%s' doesn't have identifiers for your system",name);
		return;
	}

	if(identifiers_os->get_type() != ParserNodeTypeLabeledArray)
	{
		Global::errorsManager.add_error("Function '%s' identifiers for your system has an invalid structure",name);
		return;
	}

	ParserNodeArray* identifiers_os_array = static_cast<ParserNodeArray*>(static_cast<ParserNodeLabeledArray*>(identifiers_os)->getNodeValue());

	CVector<ParserNode*> identifiers_os_elements = identifiers_os_array->getNodes();

	CVector<ParserNode*>::iterator it = identifiers_os_elements.begin();

	void* address = NULL;

	int i=1;
	while(it != identifiers_os_elements.end())
	{
		ParserNode* identifier = *(it++);

		switch(identifier->get_type())
		{
			case ParserNodeTypeArray :
			{
				ParserNodeArray* identifier_as_array = static_cast<ParserNodeArray*>(identifier);

				CVector<ParserNode*> identifier_nodes = identifier_as_array->getNodes();

				unsigned short* signature = new unsigned short[identifier_nodes.size()];

				bool invalid = false;

				for(unsigned int j=0;j<identifier_nodes.size();j++)
				{
					ParserNode* identifier_node = identifier_nodes[j];

					switch (identifier_node->get_type())
					{
						case ParserNodeTypeNum :
						{
							ParserNodeNum* identifier_node_num = static_cast<ParserNodeNum*>(identifier_node);

							int num = identifier_node_num->get_num();

							if((num < 0) || (num > 0xFF))
							{
								Global::errorsManager.add_error("Function '%s' identifier number %d field number %d for your system must be a number between 0 and 0xFF",name,i,j+1);
								invalid = true;
							}
							else
							{
								signature[j] = (short) num;
							}

							break;
						}
						case ParserNodeTypeString :
						{
							ParserNodeString* identifier_node_string = static_cast<ParserNodeString*>(identifier_node);
							char* str = identifier_node_string->get_str();

							if(!strcmp(str,"?"))
							{
								signature[j] = 0x100;
							}
							else if(!strcmp(str,"*"))
							{
								signature[j] = 0x1000;
							}
							else
							{
								Global::errorsManager.add_error("Function '%s' identifier number %d field number %d for your system must be a '?' or a '*'",name,i,j+1);
								invalid = true;
							}

							break;
						}
						default:
						{
							Global::errorsManager.add_error("Function '%s' identifier number %d field number %d for your system has an invalid structure",name,i,j+1);
							invalid = true;
							break;
						}
					}
				}

				if(!invalid)
				{
					address = library->get_address_by_sig(signature,identifier_nodes.size());
					
					if(!address)
					{
						int len = identifier_nodes.size();

						if(len > 5)
							len = 5;

						char* signature_str = new char[len*8];
					
						sprintf(signature_str,"{");

						for(int l=0;l<len;l++)
						{
							if(signature[l] & 0x100)
							{
								sprintf(signature_str,"%s ?",signature_str,signature[l]);
							}
							else if (signature[l] & 0x1000)
							{
								sprintf(signature_str,"%s *",signature_str,signature[l]);
							}
							else
							{
								sprintf(signature_str,"%s 0x%x",signature_str,signature[l]);
							}
						}

						sprintf(signature_str,"%s ... }",signature_str);

						Global::errorsManager.add_error("Function '%s' signature %s for your system was not found",name,signature_str,i);

						delete[] signature_str;
					}
				
				}

				delete[] signature;

				break;
			}
			case ParserNodeTypeString :
			{
				char* func_sym = static_cast<ParserNodeString*>(identifier)->get_str();
				address = library->get_address_by_name(func_sym);

				if(!address)
				{
					Global::errorsManager.add_error("Function '%s' identifier '%s' for your system was not found",name,func_sym);
				}

				break;
			}
			case ParserNodeTypeNum :
			{
				address = library->get_address_by_offset(static_cast<ParserNodeNum*>(identifier)->get_num());
				break;
			}
			case ParserNodeTypeLabeledScalar :
			{
				ParserNode* identifier_scalar = static_cast<ParserNodeLabeledScalar*>(identifier)->getNodeValue();

				if(identifier_scalar->get_type() != ParserNodeTypeString)
				{
					Global::errorsManager.add_error("Function '%s' identifier number %d for your system has an invalid structure",name,i);
					break;
				}

				char* module_label = static_cast<ParserNodeString*>(identifier_scalar)->get_str();

				ModuleForRage** module_ptr = Global::modulesManager.get_by_label(module_label);

				if(!module_ptr)
				{
					Global::errorsManager.add_error("Function '%s' asked for module '%s' as an identifier but it wasn't found",name,module_label);
					break;
				}

				ModuleForRage* module = *module_ptr;

				HandlerForRage* handler = handler_creator->create();
				Global::handlerManager.add(handler);

				FunctionIncomplete* function_incomplete = new FunctionIncomplete(func_name,handler,library);
				
				module->LoadedFunctionIncomplete(function_incomplete);
				
				return;
			}
			default :
			{
				Global::errorsManager.add_error("Function '%s' identifier number %d for your system has an invalid structure",name,i);
				break;
			}
		}

		if(address)
		{
			break;
		}

		i++;
	}

	if(!address)
	{
		Global::errorsManager.add_error("Function '%s' will be unusable since there wasn't any working identifier for your system",name);
		return;
	}

	HandlerForRage* handler = handler_creator->create();
	Global::handlerManager.add(handler);

	Global::functionCreator.create_function(func_name,address,handler,library);
}

void parse_virtual_function(Library* library,char* path,char* name)
{
	ParserNode* root = parse(path);

	if(!root)
	{
		return;
	}

	if(root->get_type() != ParserNodeTypeLabeledArray)

	{
		Global::errorsManager.add_error("The file for the virtual function '%s' has an invalid structure",name);
		return;
	}

	ParserNodeLabeledArray* root_labeled_array = static_cast<ParserNodeLabeledArray*>(root);

	char* func_name = root_labeled_array->getNodeLabel()->get_str();

	if(Global::virtualFunctionsManager.get_by_label(func_name))
	{
		return;
	}

	ParserNodeArray* root_array = static_cast<ParserNodeArray*>(root_labeled_array->getNodeValue());
	
	ParserNode* handler_node = root_array->getLabeledNode("handler");

	if(!handler_node)
	{
		Global::errorsManager.add_error("The file for the virtual function '%s' doesn't have a 'handler' entry",name);
		return;
	}

	if(handler_node->get_type() != ParserNodeTypeLabeledScalar)
	{
		Global::errorsManager.add_error("The file for the virtual function '%s' has the 'handler' entry with an invalid structure",name);
	}

	ParserNode* handler_value_scalar = static_cast<ParserNodeLabeledScalar*>(handler_node)->getNodeValue();

	if(handler_value_scalar->get_type() != ParserNodeTypeString)
	{
		Global::errorsManager.add_error("The file for the virtual function '%s' has the 'handler' entry with an invalid structure",name);
	}

	ParserNodeString* handler_value_string = static_cast<ParserNodeString*>(handler_value_scalar);

	char* handler_name = handler_value_string->get_str();

	HandlerCreatorForRage** handler_creator_ptr = Global::handlerCreatorManager.get_by_label(handler_name);

	if(!handler_creator_ptr)
	{
		Global::errorsManager.add_error("Virtual function '%s' is requesting handler '%s' but it isn't registered",name,handler_name);
		return;
	}

	HandlerCreatorForRage* handler_creator = *handler_creator_ptr;

	ParserNode* offsets = root_array->getLabeledNode("offsets");

	if(!offsets)
	{
		Global::errorsManager.add_error("Virtual function '%s' doesn't have an 'offsets' entry",name);
		return;
	}

	if(offsets->get_type() != ParserNodeTypeLabeledArray)
	{
		Global::errorsManager.add_error("Function '%s' has the 'identifiers' entry with an invalid structure",name);
		return;
	}

	if(!strcmp(library->get_name(),"mod"))
	{
		ParserNodeArray* offsets_array = static_cast<ParserNodeArray*>(static_cast<ParserNodeLabeledArray*>(offsets)->getNodeValue());

		if(Global::Alias)
			offsets = offsets_array->getLabeledNode(Global::Alias);
		else
			offsets = offsets_array->getLabeledNode(Global::Mod);
		
		if(!offsets)
		{
			Global::errorsManager.add_error("Virtual function '%s' doesn't have offsets for your mod",name);
			return;
		}
	}

	if(offsets->get_type() != ParserNodeTypeLabeledArray)
	{
		Global::errorsManager.add_error("Virtual function '%s' identifiers for your mod has an invalid structure",name);
		return;
	}

	ParserNodeArray* offsets_array = static_cast<ParserNodeArray*>(static_cast<ParserNodeLabeledArray*>(offsets)->getNodeValue());

	ParserNode* offsets_os = offsets_array->getLabeledNode(Global::OS);

	if(!offsets_os)
	{
		Global::errorsManager.add_error("Virtual function '%s' doesn't have an offset for your system",name);
		return;
	}

	if(offsets_os->get_type() != ParserNodeTypeLabeledScalar)
	{
		Global::errorsManager.add_error("Virtual function '%s' offset for your system has an invalid structure",name);
		return;
	}

	ParserNode* offset_os_scalar = static_cast<ParserNode*>(static_cast<ParserNodeLabeledScalar*>(offsets_os)->getNodeValue());

	if(offset_os_scalar->get_type() != ParserNodeTypeNum)
	{
		Global::errorsManager.add_error("Virtual function '%s' offset for your system has an invalid structure",name);
		return;
	}

	ParserNodeNum* offset_os_num = static_cast<ParserNodeNum*>(offset_os_scalar);

	int offset = offset_os_num->get_num();

	ParserNode* vtable = root_array->getLabeledNode("vtable");

	if(!vtable)
	{
		Global::errorsManager.add_error("Virtual function '%s' doesn't have a 'vtable' entry",name);
		return;
	}

	if(vtable->get_type() != ParserNodeTypeLabeledScalar)
	{
		Global::errorsManager.add_error("Virtual function '%s' has a 'vtable' entry with an invalid structure",name);
		return;
	}

	ParserNode* vtable_value = static_cast<ParserNodeLabeledScalar*>(vtable)->getNodeValue();

	if(vtable_value->get_type() != ParserNodeTypeString)
	{
		Global::errorsManager.add_error("Virtual function '%s' has a 'vtable' entry with an invalid structure",name);
		return;
	}

	char* vtable_value_str = static_cast<ParserNodeString*>(vtable_value)->get_str();

	int* vtable_offset_ptr = Global::vtableOffsets.retrieve(vtable_value_str);

	if(!vtable_offset_ptr)
	{
		Global::errorsManager.add_error("Virtual function '%s' asked for 'vtable' '%s' but it isn't registered",name,vtable_value_str);
		return;
	}

	int vtable_offset = *vtable_offset_ptr;

	VirtualFunction* virtualFunction = new VirtualFunction(func_name,handler_creator,vtable_offset,offset,library);

	Global::virtualFunctionsManager.add(func_name,virtualFunction);

	Global::modulesManager.LoadedVirtualFunction(virtualFunction);
}

void parse_non_virtual_functions(char* library_label,Library* library)
{
	static char functions_path[150];
	sprintf(functions_path,"%s/addons/rage/functions/%s",Global::Mod,library_label);

	DIR* dir = opendir(functions_path);

	if(!dir)
	{
		Global::errorsManager.add_error("Unable to open functions directory for library '%s'",library_label);
		return;
	}

	dirent* dir_child;
	
	while( (dir_child = readdir(dir)) != NULL)
	{
		char* name = dir_child->d_name;

		if(name[0] == '.') 
			continue;
		
		char handler_path[250];
		sprintf(handler_path,"%s/%s",functions_path,name);

		parse_function(library,handler_path,name);
	}
}

void parse_virtual_functions(char* library_label,Library* library)
{
	static char functions_path[150];
	sprintf(functions_path,"%s/addons/rage/virtual_functions/%s",Global::Mod,library_label);

	DIR* dir = opendir(functions_path);

	if(!dir)
	{
		Global::errorsManager.add_error("Unable to open virtual functions directory for library '%s'",library_label);
		return;
	}

	dirent* dir_child;
	
	while( (dir_child = readdir(dir)) != NULL)
	{
		char* name = dir_child->d_name;

		if(name[0] == '.') 
			continue;
		
		char handler_path[250];
		sprintf(handler_path,"%s/%s",functions_path,name);

		parse_virtual_function(library,handler_path,name);
	}
}

void parse_functions(char* library_label,Library* library)
{
	parse_non_virtual_functions(library_label,library);
	parse_virtual_functions(library_label,library);
}

bool file_exists(char* path)
{
	FILE* f = fopen(path,"r");
	
	if(!f)
		return false;
	
	fclose(f);
	return true;
}

void parse_vtable(char* name,char* path)
{

	if(Global::vtableOffsets.retrieve(name))
	{
		Global::errorsManager.add_error("Tried to set vtable information for '%s' when it was already set",name);
		return;
	}

	ParserNode* root = parse(path);

	if(!root)
	{
		Global::errorsManager.add_error("Unable to get vtable information for '%s'",name);
		return;
	}

	if(root->get_type() != ParserNodeTypeArray)
	{
		Global::errorsManager.add_error("Vtable information in file '%s' has an unexpected structure",path);
		return;
	}

	ParserNodeArray* root_array = static_cast<ParserNodeArray*>(root);

	ParserNode* offset = root_array->getLabeledNode(Global::OS);

	if(!offset)
	{
		Global::errorsManager.add_error("Vtable information in file '%s' doesn't have an entry for your OS",path);
		return;
	}

	if(offset->get_type() != ParserNodeTypeLabeledScalar)
	{
		Global::errorsManager.add_error("Vtable information in file '%s' has an entry for your OS with an unexpected structure",path);
		return;
	}

	ParserNode* offset_scalar = static_cast<ParserNodeLabeledScalar*>(offset)->getNodeValue();

	if(offset_scalar->get_type() != ParserNodeTypeNum)
	{
		Global::errorsManager.add_error("Vtable information in file '%s' has an entry for your OS with an unexpected structure",path);
		return;
	}

	ParserNodeNum* offset_num = static_cast<ParserNodeNum*>(offset_scalar);

	Global::vtableOffsets.insert(name,offset_num->get_num());
}

void parse_new_vtables()
{
	static char vtables_path[200];
	sprintf(vtables_path,"%s/addons/rage/config/vtables",Global::Mod);

	DIR* dir = opendir(vtables_path);

	if(!dir)
	{
		Global::errorsManager.add_error("Unable to find vtables directory");
		return;
	}

	dirent* dir_child;
	
	while( (dir_child = readdir(dir)) != NULL)
	{
		char* name = dir_child->d_name;

		if(name[0] == '.') 
			continue;

		if(Global::vtableOffsets.retrieve(name))
			continue;
		
		char vtable_path[270];

		if(Global::Alias)
			sprintf(vtable_path,"%s/%s/mods/%s",vtables_path,name,Global::Alias);
		else
			sprintf(vtable_path,"%s/%s/mods/%s",vtables_path,name,Global::Mod);
		
		if(file_exists(vtable_path))
		{
			parse_vtable(name,vtable_path);
			continue;
		}
		
		sprintf(vtable_path,"%s/%s/%s",vtables_path,name,name);

		if(file_exists(vtable_path))
		{
			parse_vtable(name,vtable_path);
			continue;
		}
		
		Global::errorsManager.add_error("Unable to get vtable information for '%s'",name);

	}

}
