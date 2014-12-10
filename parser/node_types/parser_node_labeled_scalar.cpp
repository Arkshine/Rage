
#include <parser/node_types/parser_node_labeled_scalar.h>
#include <assert.h>

ParserNodeLabeledScalar::ParserNodeLabeledScalar(ParserNodeString* nodeLabel,ParserNode* nodeValue) : ParserNodeLabeled(nodeLabel,nodeValue,ParserNodeTypeLabeledScalar)
{
	assert(
			(nodeValue->get_type() == ParserNodeTypeString)
			||
			(nodeValue->get_type() == ParserNodeTypeNum)
	);
}
