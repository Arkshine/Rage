
#include <parser/parser_node.h>

ParserNode::ParserNode(ParserNodeType type) : type(type)
{

}

ParserNodeType ParserNode::get_type()
{
	return this->type;
}