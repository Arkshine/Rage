
#ifndef _INCLUDE_PARSER_WORKER_MULTI_H_
#define _INCLUDE_PARSER_WORKER_MULTI_H_

#include <parser/parser_worker.h>
#include <parser/parser_node.h>

class ParserWorkerMulti : public ParserWorker
{
	private:

		virtual int get_workers_count() = 0;
		virtual ParserWorker** get_workers() = 0;

	public:

		ParserNode* parse();
};

#endif
