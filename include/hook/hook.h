
#ifndef __HOOK_H__
#define __HOOK_H__

#include <function/function.h>

typedef struct
{
	Function* function;
	int phase;
} Hook;

#endif
