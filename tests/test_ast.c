#include "util.h"
#include "ast.h"
#include "lex.h"


void print_exp(A_Exp exp);
void print_statement(A_Stm stm);



int main(void) {
     char* f_path = "tests/source_files/first.straight";
     FILE* fd = fopen(f_path, "r");
     Lexer lexer = make_lexer();
     
     char* input;
     size_t size;
     size_t line_pos = 0;

     while (getline(&input, &size, fd) != -1) {
            line_pos++;
	    lexer->pos = 0;
	    lexer = read_tokens(lexer, input, size, line_pos);
     }
     free(input);
     fclose(fd);

     RawToken EOF_Token = (RawToken)checked_malloc(sizeof(struct RawToken_));
     EOF_Token->token = END_OF_FILE;
     EOF_Token->text_size = 0;
     EOF_Token->line_pos = line_pos;
     
     lexer = enqueue_token(lexer, EOF_Token);

     A_Stm AST_Root = parse_source_code(lexer);

     print_statement(AST_Root);

     return EXIT_SUCCESS;
}



void print_exp(A_Exp exp) {
      if (exp == NULL)
          return;
      if (exp->kind == ID_Exp) {
          printf("\n (SUCCESS) Expression at %p is an ID_Exp\n", exp);
	  printf("\nValue is %s\n", exp->u.id_exp.id);
	  return;
      }
      else if (exp->kind == Num_Exp) {
          printf("\n (SUCCESS) xpression %p is a Num_Exp\n", exp);
	  printf("\n Value is %d\n", exp->u.num_exp.num);
	  return;
      }
      else if (exp->kind == Op_Exp) {
            printf("\n (SUCCESS) Expression at %p is an Op_Exp\n", exp);
	    print_exp(exp->u.op_exp.exp1);
	    print_exp(exp->u.op_exp.exp2);
      }
      else if (exp->kind == Eseq_Exp) {
           printf("\n (SUCCESS) Expression at %p is an Eseq_Exp\n", exp);
	   print_statement(exp->u.eseq_exp.stm);
	   print_exp(exp->u.eseq_exp.exp);
      }
      else {
           printf("\n (FAILURE) Expression junk at %p? \n", exp);
           _Exit(-1);
      }
}

void print_statement(A_Stm stm) {
     if (stm == NULL)
        return;

     if (stm->kind == AssignStm) {
         printf("\n (SUCCESS) Statement at %p is an AssignStm\n", stm);
	 printf("\n Has ID(%s)\n", stm->u.assign_stm.id);
	 print_exp(stm->u.assign_stm.exp);
	 return;
     }
     else if (stm->kind == ExpStm) {
         printf("\n (SUCCESS) Statement at %p is an ExpStm\n", stm);
	 print_exp(stm->u.expression_stm.exp);
	 return;
     }
     else if (stm->kind == PrintStm) {
         printf("\n (SUCCESS) Statement at %p is an PrintStm\n", stm);

	 A_ExpList head = stm->u.print_stm.exp_list;
	 while (head != NULL) {
	      A_Exp current_exp = head->exp;
	      printf("\nEXP_LIST_NODE\n");
	      print_exp(current_exp);
	      head = head->tail;
	 }
	 return;
     }
     else if (stm->kind == CompoundStm) {
         printf("\n (SUCCESS) Statement at %p is a CompoundStm\n", stm);
	 print_statement(stm->u.compound_stm.stm1);
	 print_statement(stm->u.compound_stm.stm2);	 
     }
     else {
          printf("\n (FAILURE) Statement junk at %p? \n", stm);
	  _Exit(-1);
     }
}
