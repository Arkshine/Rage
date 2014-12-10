
#ifndef _INCLUDE_PARSER_NODE_NUM_H_
#define _INCLUDE_PARSER_NODE_NUM_H_

#include <parser/parser_node.h>

class ParserNodeNum : public ParserNode
{
	private:

		int num;

	public:

		ParserNodeNum(int num);
		int get_num();
};


#endif