
#ifndef _INCLUDE_PARSER_WORKER_SCALAR_H_
#define _INCLUDE_PARSER_WORKER_SCALAR_H_

#include <parser/worker_types/parser_worker_multi.h>

class ParserWorkerScalar : public ParserWorkerMulti
{
	private:

		ParserWorker* workers[3];
		int get_workers_count();
		ParserWorker** get_workers();

	public:
		ParserWorkerScalar();
};

#endif
