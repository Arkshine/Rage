
#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <library/library.h>

void parse_config();

void parse_functions(char* library_label,Library* library);
void parse_new_vtables();

#endif