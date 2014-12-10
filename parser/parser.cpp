
#include <parser/parser.h>
#include <stddef.h>
#include <parser/filehandler.h>
#include <parser/worker_types/parser_worker_array_entry.h>
#include <global/global.h>

ParserNode* parse(char* filename)
{
	FILE* f = fopen(filename,"r");

	if(!f)
	{
		return NULL;
	}

	FileHandling fh(f);
	FileHandler = &fh;

	ParserNode* node = ParserWorkerArrayEntry().parse();
	
	if(FileHandler->has_error())
	{
		Global::errorsManager.add_error("Error when parsing file '%s': %s",filename,FileHandler->get_error());
		return NULL;
	}
	
	FileHandler->advance_whitespace();

	int c = FileHandler->nextc();

	if(c != EOF)
	{
		Global::errorsManager.add_error("Unexpected data in file '%s' at line %d, column %d",filename,FileHandler->get_current_line(),FileHandler->get_current_line_nchar());
		return NULL;
	}

	return node;
}
