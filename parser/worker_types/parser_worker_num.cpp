
#include <parser/worker_types/parser_worker_num.h>

int ParserWorkerNum::get_num()
{
	int multiplier = 1;
	return get_num(multiplier);
}

int ParserWorkerNum::get_num(int& multiplier)
{
	int c = FileHandler->nextc();

	if(!valid_char(c))
	{
		return 0;
	}

	FileHandler->getc();

	int add = get_num(multiplier);
		
	int num = multiplier;
	num *= char_to_num(c);

	multiplier *= base();

	return add + num;
}
