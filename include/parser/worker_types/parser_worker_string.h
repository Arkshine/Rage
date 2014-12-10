
#ifndef _INCLUDE_PARSER_WORKER_STRING_H_
#define _INCLUDE_PARSER_WORKER_STRING_H_

#include <parser/parser_worker.h>

class ParserWorkerString : public ParserWorker
{
	private:
		
		bool char_valid(int c);

	public:

		ParserNode* parse();
		
};

#endif
