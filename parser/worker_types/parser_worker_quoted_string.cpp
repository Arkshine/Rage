
#include <parser/worker_types/parser_worker_quoted_string.h>
#include <parser/node_types/parser_node_string.h>

ParserNode* ParserWorkerQuotedString::parse()
{
	FileHandler->advance_whitespace();

	int c = FileHandler->nextc();

	if(c != '"')
	{
		return NULL;
	}

	FileHandler->getc();

	int snapshot_str_start = FileHandler->create_snapshot();

	int len = 0;

	while(true)
	{
		int c = FileHandler->getc();
			
		if(c == EOF)
		{
			FileHandler->set_error("Reached end of the file while reading a quoted string");
			return NULL;
		}
		else if(c == '"')
		{
			int snapshot_str_after = FileHandler->create_snapshot();

			FileHandler->restore_snapshot(snapshot_str_start);

			ParserNodeString* node = new ParserNodeString();

			char* str = node->get_str();
			FileHandler->my_fread(str,1,len);
			str[len] = 0;

			FileHandler->restore_snapshot(snapshot_str_after);

			return node;
		}

		len++;
	}
	
	assert(false);
}
