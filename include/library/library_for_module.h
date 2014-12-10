
#ifndef _INCLUDE_LIBRARY_FOR_MODULE__H_
#define _INCLUDE_LIBRARY_FOR_MODULE__H_

class LibraryForModule
{
	public:

		virtual char* get_name() = 0;
		virtual void* get_address_by_name(char* func_name) = 0;
		virtual void* get_address_by_offset(long offset) = 0;
		virtual void* get_address_by_sig(unsigned short* signature, int length) = 0;
		virtual long  get_offset_of_address(void* address) = 0;
		virtual void* get_base_address() = 0;
		virtual long get_length() = 0;
		
};

#endif
