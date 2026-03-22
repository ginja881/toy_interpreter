#ifndef __AST_H__
#define __AST_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "symbol.h"
#include "util.h"
#include "lex.h"


typedef enum {
    OP_MUL,
    OP_DIV,
    OP_ADD,
    OP_SUB
} BinOp;


// Struct defs for grammar rules
struct A_Stm_ {
     enum {PrintStm, CompoundStm, AssignStm, ExpStm} kind;
     union {
         struct {struct A_ExpList_* exp_list;} print_stm;
	 struct {struct A_Stm_* stm1; struct A_Stm_* stm2;} compound_stm;
	 struct {string id; struct A_Exp_* exp;} assign_stm;
	 struct {struct A_Exp_* exp;} expression_stm;
     } u;
};

struct A_Exp_ {
    enum {ID_Exp, Op_Exp, Eseq_Exp, Num_Exp} kind;
    union {
       struct {string id;} id_exp;
       struct {int num;} num_exp;
       struct {struct A_Exp_* exp1; struct A_Exp_* exp2; BinOp op;} op_exp;
       struct {struct A_Stm_* stm; struct A_Exp_* exp;} eseq_exp;
    } u;
};

struct A_ExpList_ {
    struct A_Exp_* exp; 
    struct A_ExpList_* tail;
};

// Type aliases
typedef struct A_Stm_* A_Stm;
typedef struct A_Exp_* A_Exp;
typedef struct A_ExpList_* A_ExpList;

// Constructor definitions

A_Stm compound_stm(A_Stm stm1, A_Stm stm2);
A_Stm print_stm(A_ExpList exp_list);
A_Stm assign_stm(string id, A_Exp exp);
A_Stm expression_stm(A_Exp exp);

A_Exp id_exp(string id);
A_Exp num_exp(int num);
A_Exp eseq_exp(A_Stm stm, A_Exp exp);
A_Exp op_exp(A_Exp exp1, BinOp op, A_Exp exp2);

A_ExpList exp_list(A_Exp exp);

// Miscellaneous functions
int max_args_stm(A_Stm stm);
int max_args_exp(A_ExpList exp_list);


// Recursive Descent

BinOp get_op(Token operator);

int match(Token token_type, Lexer lexer);




A_Exp parse_literal(Lexer lexer);
A_Exp parse_factor(Lexer lexer);
A_Exp parse_term(Lexer lexer);

A_ExpList parse_expression_list(Lexer lexer);
int check_next_stm(Lexer lexer);
A_Exp parse_expression(Lexer lexer);
A_Stm parse_statement(Lexer lexer);
A_Stm parse_source_code(Lexer lexer);


#endif
