
#include <parser/node_types/parser_node_array.h>

ParserNodeArray::ParserNodeArray() : ParserNode(ParserNodeTypeArray)
{

}

void ParserNodeArray::addNode(ParserNode* node)
{
	nodes.push_back(node);
}

bool ParserNodeArray::addLabeledNode(ParserNode* node, char* label)
{
	if(getLabeledNode(label))
		return false;

	labeledNodes.insert(label,node);
	addNode(node);

	return true;
}

ParserNode* ParserNodeArray::getNode(unsigned int id)
{
	if(id >= nodes.size())
		return NULL;

	return nodes.at(id);
}

ParserNode* ParserNodeArray::getLabeledNode(char *label)
{
	if(labeledNodes.retrieve(label))
		return *labeledNodes.retrieve(label);

	return NULL;
}

CVector<ParserNode*> ParserNodeArray::getNodes()
{
	return this->nodes;
}
