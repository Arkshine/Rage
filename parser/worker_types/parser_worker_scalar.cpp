
#include <parser/worker_types/parser_worker_scalar.h>

#include <parser/worker_types/parser_worker_any_string.h>
#include <parser/worker_types/parser_worker_decimal.h>
#include <parser/worker_types/parser_worker_hex.h>

#include <parser/filehandler.h>

int ParserWorkerScalar::get_workers_count()
{
	return sizeof(this->workers) / sizeof(ParserWorker*);
}

ParserWorker** ParserWorkerScalar::get_workers()
{
	return workers;
}

ParserWorkerScalar::ParserWorkerScalar()
{
	workers[0] = new ParserWorkerHex();
	workers[1] = new ParserWorkerDecimal();
	workers[2] = new ParserWorkerAnyString();	
}
