
#ifndef _INCLUDE_PARSER_WORKER_LABELED_SCALAR_H_
#define _INCLUDE_PARSER_WORKER_LABELED_SCALAR_H_

#include <parser/parser_worker.h>
#include <parser/parser_node.h>

class ParserWorkerLabeledScalar : public ParserWorker
{
	public:
		ParserNode* parse();
};

#endif
