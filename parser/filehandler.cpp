
#include <parser/filehandler.h>

FileHandling* FileHandler = NULL;

FileHandling::FileHandling(FILE* file) : file(file) , error_set(false)
{
	assert(!this->has_error());
	current_info.line = 1;
	current_info.line_nchar = 1;
}

int FileHandling::create_snapshot()
{
	assert(!this->has_error());
	FileHandlingInfo info;
	info.line = current_info.line;
	info.line_nchar = current_info.line_nchar;
	fgetpos(file,&info.pos);
		
	snapshots.push_back(info);
	return snapshots.size() - 1;
}

void FileHandling::restore_snapshot(int id)
{
	assert(!this->has_error());
	current_info = snapshots.at(id);
	fsetpos(file,&current_info.pos);
}

size_t FileHandling::my_fread(void* ptr,size_t size,size_t count)
{
	assert(!this->has_error());
	return fread(ptr,size,count,this->file);
}

int FileHandling::getc()
{
	assert(!this->has_error());
	current_info.line_nchar++;
	return fgetc(file);
}

int FileHandling::nextc()
{
	assert(!this->has_error());

	int snap_pre = FileHandler->create_snapshot();

	int c = fgetc(file);

	FileHandler->restore_snapshot(snap_pre);

	return c;
}

void FileHandling::advance_whitespace()
{
	assert(!this->has_error());
	int last = ~'\r';

	while(true)
	{
		int snap_pre = FileHandler->create_snapshot();

		int c = fgetc(file);

		switch(c)
		{
			case '\n' :
			{
				if(last != '\r')
				{
					current_info.line++;
					current_info.line_nchar = 1;
				}
				break;
			}

			case '\r' :
			{
				current_info.line++;
				current_info.line_nchar = 1;
				break;
			}

			case '\t' :
			case ' ' :
			{
				current_info.line_nchar++;
				break;
			}

			default :
			{
				if((c > 0 ) && ((c<32) || (c>126)))
					break;

				FileHandler->restore_snapshot(snap_pre);

				return;
			}
		}

		last = c;
	}
}

FileHandling::~FileHandling()
{
	fclose(this->file);
}

int FileHandling::get_current_line()
{
	return this->current_info.line;
}

int FileHandling::get_current_line_nchar()
{
	return this->current_info.line_nchar;
}

#include <stdarg.h>

void FileHandling::set_error(char* format,...)
{
	va_list argptr;
	va_start(argptr,format);
	
	vsprintf(this->error,format,argptr);

	va_end(argptr);

	this->error_set = true;
}

char* FileHandling::get_error()
{
	return this->error;
}

bool FileHandling::has_error()
{
	return this->error_set;
}