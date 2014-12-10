
#ifndef _INCLUDE_PARSER_NODE_H_
#define _INCLUDE_PARSER_NODE_H_

#include <parser/parser_node_type.h>

class ParserNode
{
	ParserNodeType type;


	public:

		ParserNodeType get_type();
		ParserNode(ParserNodeType type);
};

#endif
