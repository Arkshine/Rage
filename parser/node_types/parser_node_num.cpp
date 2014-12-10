
#include <parser/node_types/parser_node_num.h>

ParserNodeNum::ParserNodeNum(int num) : ParserNode(ParserNodeTypeNum) , num(num) 
{

}

int ParserNodeNum::get_num()
{
	return this->num;
}
