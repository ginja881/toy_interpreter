#include "util.h"
#include "ast.h"
#include "lex.h"

int main(void) {
     char* f_path = "tests/source_files/second.straight";
     FILE* fd = fopen(f_path, "r");
     Lexer lexer = make_lexer();
     lexer = read_tokens(lexer, fd);

     A_Stm root = parse_source_code(lexer);
     do {
           A_Stm main_stm = root->u.compound_stm.stm1; 
           if (main_stm->kind == PrintStm)
	      printf("\n Print Stm\n");
	   else if (main_stm->kind == AssignStm)
	      printf("\n Assign Stm\n");
	   else if (main_stm->kind == ExpStm)
	      printf("\n Exp Stm\n");
	      
	   root = root->u.compound_stm.stm2;
     } while (root->kind == CompoundStm);

     fclose(fd);
     return EXIT_SUCCESS;
}
