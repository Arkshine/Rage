
#ifndef _INCLUDE_PARSER_WORKER_NUM_H_
#define _INCLUDE_PARSER_WORKER_NUM_H_

#include <parser/parser_worker.h>
#include <parser/filehandler.h>

class ParserWorkerNum : public ParserWorker
{
	protected:

		virtual bool valid_char(int c) = 0;
		virtual int base() = 0;
		virtual int char_to_num(int c) = 0;

		int get_num();
		int get_num(int& multiplier);
};

#endif
