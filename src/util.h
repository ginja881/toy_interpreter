#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

#define UNFINISHED_STATEMENT -1
#define INVALID_CHARACTER -10
#define SYNTAX_ERROR -5


typedef const char*  string;

string String(char* text);
void* checked_malloc(size_t size);
int max(int a, int b);
int min(int a, int b);

void error(int error_code, int position);

#endif
