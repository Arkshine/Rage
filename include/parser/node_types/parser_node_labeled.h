
#ifndef _INCLUDE_PARSER_NODE_LABELED_H_
#define _INCLUDE_PARSER_NODE_LABELED_H_

#include <parser/parser_node.h>
#include <parser/node_types/parser_node_string.h>
#include <parser/parser_node_type.h>

class ParserNodeLabeled : public ParserNode
{
		ParserNodeString* nodeLabel;
		ParserNode* nodeValue;

	public:
		
		ParserNodeLabeled(ParserNodeString* nodeLabel,ParserNode* nodeValue,ParserNodeType type);
		ParserNodeString* getNodeLabel();
		ParserNode* getNodeValue();
};


#endif
