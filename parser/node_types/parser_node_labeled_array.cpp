
#include <parser/node_types/parser_node_labeled_array.h>
#include <assert.h>

ParserNodeLabeledArray::ParserNodeLabeledArray(ParserNodeString* nodeLabel,ParserNode* nodeValue) : ParserNodeLabeled(nodeLabel,nodeValue,ParserNodeTypeLabeledArray)
{
	assert(
			(nodeValue->get_type() == ParserNodeTypeArray)
	);

}
