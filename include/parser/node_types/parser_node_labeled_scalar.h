
#ifndef _INCLUDE_PARSER_NODE_LABELED_STRING_H_
#define _INCLUDE_PARSER_NODE_LABELED_STRING_H_

#include <parser/parser_node.h>
#include <parser/node_types/parser_node_labeled.h>

class ParserNodeLabeledScalar : public ParserNodeLabeled
{
	public:
		
		ParserNodeLabeledScalar(ParserNodeString* nodeLabel,ParserNode* nodeValue);
};


#endif
