#include "util.h"

string String(char* text) {
     return (string) text;
}

void* checked_malloc(size_t size) {
     void* data = malloc(size);
     assert(data);
     return data;
}

int max(int a, int b) {
    return (a < b) ? b : a;
}

int min(int a, int b) {
   return (a < b) ? a : b;
}

void error(int error_code, int pos) {
    switch(error_code) {
        
	case SYNTAX_ERROR:
	    fprintf(stderr, "Syntax error at %d", pos);
	    break;
        case INVALID_CHARACTER:
	    fprintf(stderr, "Invalid character at %d", pos);
	    break;
    }
    _Exit(-1);
}
