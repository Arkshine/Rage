
#include <parser/worker_types/parser_worker_array_entry.h>

#include <parser/worker_types/parser_worker_array.h>
#include <parser/worker_types/parser_worker_labeled_array.h>
#include <parser/worker_types/parser_worker_labeled_scalar.h>
#include <parser/worker_types/parser_worker_scalar.h>

#include <parser/filehandler.h>

int ParserWorkerArrayEntry::get_workers_count()
{
	return sizeof(this->workers) / sizeof(ParserWorker*);
}

ParserWorker** ParserWorkerArrayEntry::get_workers()
{
	return workers;
}

ParserWorkerArrayEntry::ParserWorkerArrayEntry()
{
	workers[0] = new ParserWorkerLabeledArray();
	workers[1] = new ParserWorkerLabeledScalar();
	workers[2] = new ParserWorkerArray();
	workers[3] = new ParserWorkerScalar();	
}
