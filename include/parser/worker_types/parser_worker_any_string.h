
#ifndef _INCLUDE_PARSER_WORKER_ANY_STRING_H_
#define _INCLUDE_PARSER_WORKER_ANY_STRING_H_

#include <parser/worker_types/parser_worker_multi.h>

class ParserWorkerAnyString : public ParserWorkerMulti
{
	private:

		ParserWorker* workers[2];
		int get_workers_count();
		ParserWorker** get_workers();

	public:
		ParserWorkerAnyString();
};

#endif
