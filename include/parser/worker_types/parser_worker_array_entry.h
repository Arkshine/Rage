
#ifndef _INCLUDE_PARSER_WORKER_ARRAY_ENTRY_H_
#define _INCLUDE_PARSER_WORKER_ARRAY_ENTRY_H_

#include <parser/worker_types/parser_worker_multi.h>

class ParserWorkerArrayEntry : public ParserWorkerMulti
{
	private:

		ParserWorker* workers[4];
		int get_workers_count();
		ParserWorker** get_workers();

	public:

		ParserWorkerArrayEntry();
};

#endif
