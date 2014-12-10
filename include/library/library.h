
#ifndef _INCLUDE_LIBRARY__H_
#define _INCLUDE_LIBRARY__H_

#include <library/library_for_module.h>

class Library : public LibraryForModule
{
	private:

		void *handle;
		void *base_address;
		long length;

		void do_close();

		char name[50];

	public:

		Library(void *handle, void* base_address, long length, char* name);
		Library(void *handle);
		~Library();
		char* get_name();
		void* get_address_by_name(char* func_name);
		void* get_address_by_offset(long offset);
		void* get_address_by_sig(unsigned short* signature, int length);
		long  get_offset_of_address(void* address);
		void* get_base_address();
		long get_length();
};

Library* create_library(char* path);
Library* create_library(void* contained_ptr,char* label);

#endif
