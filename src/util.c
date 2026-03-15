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
