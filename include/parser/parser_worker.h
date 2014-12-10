

#ifndef _INCLUDE_PARSER_WORKER_H_
#define _INCLUDE_PARSER_WORKER_H_

#include <parser/parser_node.h>
#include <parser/filehandler.h>

class ParserWorker
{
	public:	
		virtual ParserNode* parse() = 0;
};

#endif
