
#include <parser/worker_types/parser_worker_labeled_scalar.h>
#include <parser/filehandler.h>
#include <parser/node_types/parser_node_labeled_scalar.h>
#include <parser/worker_types/parser_worker_any_string.h>
#include <parser/worker_types/parser_worker_scalar.h>

ParserNode* ParserWorkerLabeledScalar::parse()
{
	FileHandler->advance_whitespace();

	int snapshot_begin = FileHandler->create_snapshot();

	ParserNode* nodeLabel = ParserWorkerAnyString().parse();

	if(!nodeLabel)
	{
		FileHandler->restore_snapshot(snapshot_begin);
		return NULL;
	}

	FileHandler->advance_whitespace();

	int c = FileHandler->getc();

	if(c != ':')
	{
		delete nodeLabel;
		FileHandler->restore_snapshot(snapshot_begin);
		return NULL;
	}

	FileHandler->advance_whitespace();

	ParserNode* nodeValue = ParserWorkerScalar().parse();

	if(FileHandler->has_error())
	{
		delete nodeLabel;
		return NULL;
	}

	if(!nodeValue)
	{
		delete nodeLabel;
		FileHandler->restore_snapshot(snapshot_begin);
		return NULL;
	}

	return new ParserNodeLabeledScalar(static_cast<ParserNodeString*>(nodeLabel),nodeValue);
}
