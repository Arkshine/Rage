
#ifndef _INCLUDE_PARSER_WORKER_QUOTED_STRING_H_
#define _INCLUDE_PARSER_WORKER_QUOTED_STRING_H_

#include <parser/parser_worker.h>

class ParserWorkerQuotedString : public ParserWorker
{
	public:

		ParserNode* parse();
};

#endif
