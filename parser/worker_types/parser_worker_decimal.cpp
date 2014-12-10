
#include <parser/worker_types/parser_worker_decimal.h>
#include <parser/filehandler.h>
#include <parser/node_types/parser_node_num.h>

bool ParserWorkerDecimal::valid_char(int c)
{
	return c>='0' && c<='9';
}

int ParserWorkerDecimal::base()
{
	return 10;
}

int ParserWorkerDecimal::char_to_num(int c)
{
	return c-'0';
}

ParserNode* ParserWorkerDecimal::parse()
{
	FileHandler->advance_whitespace();

	int c = FileHandler->nextc();
		
	if(!this->valid_char(c))
	{
		return NULL;
	}

	int num = get_num();

	return new ParserNodeNum(num);
}
