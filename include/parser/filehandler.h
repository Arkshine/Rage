
#ifndef _INCLUDE_PARSER_FILE_HANDLER_H_
#define _INCLUDE_PARSER_FILE_HANDLER_H_

#include <stdio.h>
#include <CVector.h>

class FileHandling
{
	private:

		struct FileHandlingInfo
		{
			int line;
			int line_nchar;
			fpos_t pos;
		};

		FILE* file;
		FileHandlingInfo current_info;
		CVector<FileHandlingInfo> snapshots;
		char error[200];
		bool error_set;

	public:

		char* get_error();
		bool has_error();
		FileHandling(FILE* file);
		~FileHandling();
		int create_snapshot();
		void restore_snapshot(int id);
		size_t my_fread(void* ptr,size_t size,size_t count);
		int getc();
		int nextc();
		void advance_whitespace();
		int get_current_line();
		int get_current_line_nchar();
		void set_error(char* format,...);
};

extern FileHandling* FileHandler;

#endif
