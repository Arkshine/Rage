
#include <parser/worker_types/parser_worker_any_string.h>

#include <parser/worker_types/parser_worker_string.h>
#include <parser/worker_types/parser_worker_quoted_string.h>

#include <parser/filehandler.h>

int ParserWorkerAnyString::get_workers_count()
{
	return sizeof(this->workers) / sizeof(ParserWorker*);
}

ParserWorker** ParserWorkerAnyString::get_workers()
{
	return workers;
}

ParserWorkerAnyString::ParserWorkerAnyString()
{
	workers[0] = new ParserWorkerString();
	workers[1] = new ParserWorkerQuotedString();
}