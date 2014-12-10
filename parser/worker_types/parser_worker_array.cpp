
#include <parser/worker_types/parser_worker_array.h>
#include <parser/worker_types/parser_worker_array_entry.h>
#include <parser/filehandler.h>
#include <parser/node_types/parser_node_array.h>
#include <parser/node_types/parser_node_labeled.h>

void addNodeToArray(ParserNodeArray* node_array,ParserNode* node)
{
	switch(node->get_type())
	{
		case ParserNodeTypeLabeledScalar:
		case ParserNodeTypeLabeledArray:
		{
			ParserNodeLabeled* nodeLabeled = static_cast<ParserNodeLabeled*>(node);
			node_array->addLabeledNode(nodeLabeled,nodeLabeled->getNodeLabel()->get_str());
			break;
		}
		default:
		{
			node_array->addNode(node);
			break;
		}
	}
}

ParserNode* ParserWorkerArray::parse()
{
	FileHandler->advance_whitespace();

	int nextc = FileHandler->nextc();

	if(nextc != '{')
		return NULL;

	FileHandler->getc();

	ParserNodeArray* node_array = new ParserNodeArray();
	
	ParserNode* node = ParserWorkerArrayEntry().parse();

	while(true)
	{
		if(FileHandler->has_error())
		{
			return NULL;
		}
		
		nextc = FileHandler->nextc();

		if(!node)
		{
			FileHandler->advance_whitespace();

			if(nextc == '}')
			{
				FileHandler->getc();
				return node_array;
			}
			else if(nextc == EOF)
			{
				FileHandler->set_error("Unexpected end of file while reading an array. Check if you forgot a '}'");
				return NULL;
			}
			else 
			{
				FileHandler->set_error("Unexpected chara1cter while reading an array at line %d column %d",FileHandler->get_current_line(),FileHandler->get_current_line_nchar());
				return NULL;
			}
		}
		else
		{
			addNodeToArray(node_array,node);

			if(nextc == '}')
			{
				FileHandler->getc();
				return node_array;
			}
			else if(nextc == '\t' || nextc == '\n' || nextc == '\r' || nextc == ' ' || nextc == 10)
			{
				FileHandler->advance_whitespace();

				nextc = FileHandler->nextc();

				if(nextc == ',')
				{
					FileHandler->getc();
					FileHandler->advance_whitespace();
				}
			}
			else if(nextc == ',')
			{
				FileHandler->getc();
				FileHandler->advance_whitespace();
			}
			else if(nextc == EOF)
			{
				FileHandler->set_error("Unexpected end of file while reading an array. Check if you forgot a '}'");
				return NULL;
			}
			else if(nextc != '{')
			{
				FileHandler->set_error("Unexpected character while reading an array at line %d column %d",FileHandler->get_current_line(),FileHandler->get_current_line_nchar());
				return NULL;
			}			
		}

		node = ParserWorkerArrayEntry().parse();
	}	
}
