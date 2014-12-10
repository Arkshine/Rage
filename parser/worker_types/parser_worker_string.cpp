
#include <parser/worker_types/parser_worker_string.h>
#include <parser/node_types/parser_node_string.h>

bool ParserWorkerString::char_valid(int c)
{
	return (c !='{') && (c !='}') && (c !=':') && (c !='"') && (c !=' ') && (c != ',') && (c !='\t') && (c !='\r') && (c !='\n') && (c>=32) && (c<=126);
}

ParserNode* ParserWorkerString::parse()
{
	FileHandler->advance_whitespace();

	int snapshot_begin = FileHandler->create_snapshot();

	int nextc = FileHandler->nextc();

	if(!char_valid(nextc))
	{
		return NULL;
	}

	int len = 0;
	
	int snapshot_after_string;

	while(true)
	{
		snapshot_after_string = FileHandler->create_snapshot();

		int c = FileHandler->getc();
			
		if(!char_valid(c))
		{
			break;
		}

		len++;
	}

	FileHandler->restore_snapshot(snapshot_begin);

	ParserNodeString* nodeString = new ParserNodeString();

	char* str = nodeString->get_str();
	FileHandler->my_fread(str,1,len);
	str[len] = 0;

	FileHandler->restore_snapshot(snapshot_after_string);

	assert(!char_valid(FileHandler->nextc()));

	return nodeString;
}
