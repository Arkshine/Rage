
#ifndef _INCLUDE_PARSER_WORKER_DECIMAL_H_
#define _INCLUDE_PARSER_WORKER_DECIMAL_H_

#include <parser/worker_types/parser_worker_num.h>

class ParserWorkerDecimal : public ParserWorkerNum
{
	protected:

		bool valid_char(int c);
		int base();
		int char_to_num(int c);

	public:

		ParserNode* parse();
};

#endif
