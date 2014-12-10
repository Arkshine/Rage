
#include <parser/node_types/parser_node_labeled.h>

ParserNodeLabeled::ParserNodeLabeled(ParserNodeString* nodeLabel,ParserNode* nodeValue,ParserNodeType type) : ParserNode(type) , nodeLabel(nodeLabel), nodeValue(nodeValue)
{

}

ParserNodeString* ParserNodeLabeled::getNodeLabel()
{
	return this->nodeLabel;
}

ParserNode* ParserNodeLabeled::getNodeValue()
{
	return this->nodeValue;
}
