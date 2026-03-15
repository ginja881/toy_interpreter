#ifndef __LEX_H__
#define __LEX_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "util.h"


typedef enum {
     LPAR,
     RPAR,
     ID,
     ASSIGN,
     COMMA,
     PRINT,
     NUM,
     MUL, 
     ADD, 
     SUB,
     DIV,
     SEMI_COLON
} Token;

struct RawToken_{
    Token token;
    string text;
    size_t text_size;
    struct RawToken_* next;
};

typedef struct RawToken_* RawToken;

struct TokenQueue_ {
    RawToken* token_head;
    RawToken* token_tail;
    size_t size;
};

typedef struct TokenQueue_* TokenQueue;

TokenQueue make_token_queue(void);

int is_empty(TokenQueue token_queue);
TokenQueue enqueue(TokenQueue token_queue, RawToken token);
RawToken dequeue(TokenQueue token_queue);

RawToken consume(string text);



#endif
