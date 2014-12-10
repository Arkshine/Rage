
#include <parser/worker_types/parser_worker_hex.h>
#include <parser/filehandler.h>
#include <parser/node_types/parser_node_num.h>

bool ParserWorkerHex::valid_char(int c)
{
	return (c>='0' && c<='9') || (c>='a' && c<='f') || (c>='A' && c<='F');
}

int ParserWorkerHex::base()
{
	return 0x10;
}

int ParserWorkerHex::char_to_num(int c)
{
	return ((c>='a' && c<='f') * (10+c-'a')) + ((c>='A' && c<='F') * (10+c-'A')) + ((c>='0' && c<='9') * (c-'0'));
}

ParserNode* ParserWorkerHex::parse()
{
	FileHandler->advance_whitespace();

	int snapshot_begin = FileHandler->create_snapshot();

	int c = FileHandler->getc();
		
	if(c != '0')
	{
		FileHandler->restore_snapshot(snapshot_begin);
		return NULL;
	}

	c = FileHandler->getc();

	if(c != 'x')
	{
		FileHandler->restore_snapshot(snapshot_begin);
		return NULL;
	}

	c = FileHandler->nextc();

	if(!valid_char(c))
	{
		FileHandler->set_error("Invalid hex digit at line %d, column %d",FileHandler->get_current_line(),FileHandler->get_current_line_nchar());
		return NULL;
	}

	int num = get_num();

	return new ParserNodeNum(num);
}
