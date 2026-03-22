#include "util.h"

string String(char* text) {
     // Allocate new string
     return strdup(text);
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

void error(int error_code, size_t pos, string text, size_t line_pos) {
    fprintf(stderr, "\n On Line: %ld \n", line_pos);
    switch(error_code) {
        
	case SYNTAX_ERROR:
	    fprintf(
	    	stderr, 
	    	"\n(SYNTAX_ERROR) pos=%ld, text=%s\n", 
		pos,
                text
	    );
	    break;
        case INVALID_CHARACTER:
	    fprintf(
	    	stderr, 
	    	"\nInvalid character at pos=%ld, text=%s\n", 
	    	pos,
		text
	    );
	    break;
    }
    _Exit(-1);
}
