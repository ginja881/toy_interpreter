#ifndef __LEX_H__
#define __LEX_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "util.h"


enum Token {
     L_PAREN,
     R_PAREN,
     ID,
     ASSIGN,
     PRINT,
     NUM,
     MUL, 
     PLUS, 
     SUB,
     DIV,
     COMMA,
     SEMI_COLON,
     END_OF_FILE
};
typedef enum Token Token;
struct RawToken_{
    Token token;
    string text;
    size_t pos;
    size_t line_pos;
    size_t text_size;
    struct RawToken_* next;
};

typedef struct RawToken_* RawToken;

struct TokenQueue_ {
    RawToken token_head;
    RawToken token_tail;
    size_t size;
};

struct Lexer_ {
     struct TokenQueue_* queue;
     size_t pos;
};


typedef struct TokenQueue_* TokenQueue;
typedef struct Lexer_* Lexer;

Lexer make_lexer(void);
int is_queue_empty(Lexer lexer);
Lexer enqueue_token(Lexer lexer, RawToken token);

RawToken eat_token(Lexer lexer);
RawToken peek(Lexer lexer);
RawToken next_token(Lexer lexer);

Lexer read_tokens(Lexer lexer, char* input, size_t size, size_t line_pos);


#endif
