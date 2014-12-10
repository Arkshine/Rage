
#include <parser/worker_types/parser_worker_labeled_array.h>
#include <parser/filehandler.h>
#include <parser/node_types/parser_node_labeled_array.h>
#include <parser/node_types/parser_node_string.h>
#include <parser/worker_types/parser_worker_any_string.h>
#include <parser/worker_types/parser_worker_scalar.h>
#include <parser/worker_types/parser_worker_array.h>

ParserNode* ParserWorkerLabeledArray::parse()
{
	FileHandler->advance_whitespace();

	int snapshot_begin = FileHandler->create_snapshot();

	ParserNode* nodeLabel = ParserWorkerAnyString().parse();

	if(FileHandler->has_error())
	{
		return NULL;
	}

	if(!nodeLabel)
	{
		FileHandler->restore_snapshot(snapshot_begin);
		return NULL;
	}

	FileHandler->advance_whitespace();

	int c = FileHandler->nextc();

	if(c == ':')
	{
		c = FileHandler->getc(),
		FileHandler->advance_whitespace();
	}

	ParserNode* nodeValue = ParserWorkerArray().parse();

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

	return new ParserNodeLabeledArray(static_cast<ParserNodeString*>(nodeLabel),nodeValue);	
}
