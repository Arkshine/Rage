
#include <string.h>

#include <library/library.h>

#if defined __linux__
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#else
#include <windows.h>
#include <psapi.h>
#endif

#include <stdio.h>
#include <assert.h>

Library::Library(void *handle, void* base_address, long length, char* name) : handle(handle), base_address(base_address), length(length)
{
	if(!name)
	{
		this->name[0] = 0;
	}
	else
	{
		strcpy(this->name,name);
	}
}

Library::Library(void *handle) : handle(handle), base_address(0), length(0)
{
	this->name[0] = 0;
}

char* Library::get_name()
{
	return this->name;
}

void Library::do_close()
{
	#ifdef WIN32
	FreeLibrary((HMODULE)this->handle);
	#else
	dlclose(this->handle);
	#endif
}

Library::~Library()
{
	this->do_close();
}

long Library::get_offset_of_address(void* address)
{
	return (long)address - (long)this->base_address;
}

void* Library::get_address_by_name(char* name)
{
	#ifdef WIN32
	return GetProcAddress((HMODULE)this->handle,name);
	#else
	return dlsym(this->handle,name);
	#endif
}

void* Library::get_address_by_offset(long offset)
{
	return (void*)((long)this->base_address + offset);
}

#include <util/util.h>


bool search(unsigned short* signature,int signature_length, unsigned char* address, int address_length)
{
	if(signature_length == 0)
	{
		return true;
	}

	if(*signature & 0x100)
	{
		return search(signature+1,signature_length-1,address,address_length) || search(signature+1,signature_length-1,address+1,address_length-1);
	}
	else if(*signature & 0x1000)
	{
		return search(signature+1,signature_length-1,address+1,address_length-1);
	}
	else if(*signature <= 0xFF)
	{
		if((unsigned char)*signature == *address)
		{
			return search(signature+1,signature_length-1,address+1,address_length-1);
		}
		else
		{
			return false;
		}
	}
	else
	{
		assert(0);
	}

	return false;
}

void* Library::get_address_by_sig(unsigned short* signature,int length)
{
	assert(this->base_address);
	assert(this->length);

	for(int i=0;i<=this->length - length;i++)
	{
		unsigned char* address = ((unsigned char*)this->base_address)+i;

		if(search(signature,length,address,this->length))
		{
			return address;
		}
	}

	return NULL;
}

Library* create_library(char* path)
{
	void* handle = NULL;
	
	#ifdef WIN32
	handle = LoadLibrary(path);
	#else
	handle = dlopen(path,RTLD_NOW);
	#endif

	if(handle == NULL)
		return NULL;

	return new Library(handle);
}

long getLength(void *baseAddress);

Library* create_library(void* contained_address, char* name)
{
#ifdef WIN32
	HMODULE module;
	if(!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,(LPCSTR)contained_address,&module))
		return NULL;

	HANDLE process =  GetCurrentProcess();
	_MODULEINFO moduleInfo;

	if(!GetModuleInformation(process,module,&moduleInfo,sizeof moduleInfo))
		return NULL;
	
	CloseHandle(process);

	return new Library(module,moduleInfo.lpBaseOfDll,moduleInfo.SizeOfImage,name);
#else 
	Dl_info info;

	if(!dladdr(contained_address,&info))
		return NULL;

	return new Library(dlopen(info.dli_fname, RTLD_NOW),(void*) info.dli_fbase, getLength((void*) info.dli_fbase), name);

#endif
}

#if defined __linux__
	// Code derived from code from David Anderson
	long getLength(void *baseAddress)
	{
			pid_t pid = getpid();
			char file[255];
			char buffer[2048];
			snprintf(file, sizeof(file)-1, "/proc/%d/maps", pid);
			FILE *fp = fopen(file, "rt");
			if (fp)
			{
				long length = 0;

        		void *start=NULL;
				void *end=NULL;

        		while (!feof(fp))
				{
					fgets(buffer, sizeof(buffer)-1, fp);			
#if defined AMD64
					sscanf(buffer, "%Lx-%Lx", &start, &end);
#else
					sscanf(buffer, "%lx-%lx", &start, &end);
#endif
					if(start == baseAddress)
					{
						length = (unsigned long)end  - (unsigned long)start;

						char ignore[100];
						int value;

						while(!feof(fp))
						{
							fgets(buffer, sizeof(buffer)-1, fp);
#if defined AMD64
							sscanf(buffer, "%Lx-%Lx %s %s %s %d", &start, &end, ignore, ignore, ignore, &value);
#else
	        				sscanf(buffer, "%lx-%lx %s %s %s %d", &start, &end, ignore, ignore ,ignore, &value);
#endif
							if(!value)
							{		
								break;
							}
							else
							{
								length += (unsigned long)end  - (unsigned long)start;
							}
						}
						
						break;
					}
        		}

				fclose(fp);

			return length;
		}

		return 0;
	}

#endif // LINUX

void* Library::get_base_address()
{
	return this->base_address;
}

long Library::get_length()
{
	return this->length;
}