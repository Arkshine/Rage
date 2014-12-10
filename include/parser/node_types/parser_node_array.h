
#ifndef _INCLUDE_PARSER_NODE_ARRAY_H_
#define _INCLUDE_PARSER_NODE_ARRAY_H_

#include <parser/parser_node.h>

#include "CVector.h"
#include "sm_trie_tpl.h"

class ParserNodeArray : public ParserNode
{
	private:

		CVector<ParserNode*> nodes;
		KTrie<ParserNode*> labeledNodes;

	public:

		ParserNodeArray();
		void addNode(ParserNode* node);
		bool addLabeledNode(ParserNode* node, char* label);
		ParserNode* getNode(unsigned int id);
		ParserNode* getLabeledNode(char *label);
		CVector<ParserNode*> getNodes();
};

#endif