
#ifndef _INCLUDE_PARSER_NODE_STRING_H_
#define _INCLUDE_PARSER_NODE_STRING_H_

#include <parser/parser_node.h>

class ParserNodeString : public ParserNode
{
		char str[300];

	public:
		
		ParserNodeString();
		char* get_str();
};


#endif
