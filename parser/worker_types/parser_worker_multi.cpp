
#include <parser/worker_types/parser_worker_multi.h>
#include <parser/filehandler.h>

ParserNode* ParserWorkerMulti::parse()
{
	ParserWorker** workers = this->get_workers();

	for(int i=0;i<this->get_workers_count();i++)
	{
		ParserNode* node = workers[i]->parse();

		if(FileHandler->has_error())
		{
			return NULL;
		}

		if(node)
		{
			return node;
		}
	}

	return NULL;
}