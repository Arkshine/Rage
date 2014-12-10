
#ifndef _INCLUDE_PARSER_NODE_LABELED_ARRAY_H_
#define _INCLUDE_PARSER_NODE_LABELED_ARRAY_H_

#include <parser/node_types/parser_node_array.h>
#include <parser/node_types/parser_node_labeled.h>

class ParserNodeLabeledArray : public ParserNodeLabeled
{
	public:
		
		ParserNodeLabeledArray(ParserNodeString* nodeLabel,ParserNode* nodeValue);
};


#endif
