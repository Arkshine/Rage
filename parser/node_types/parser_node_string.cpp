
#include <parser/node_types/parser_node_string.h>

ParserNodeString::ParserNodeString() : ParserNode(ParserNodeTypeString)
{
		
}

char* ParserNodeString::get_str()
{
	return this->str;
}
