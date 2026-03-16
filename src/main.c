#include "lex.h"
#include "ast.h"
#include "util.h"
#include "symbol.h"


void interp_program(A_Stm ast_root);



int main(int argc, char** argv) {
   if (argc < 2) {
       perror("Need to specify .straight file");
       return EXIT_FAILURE;
   }
   
   // Checking if file has valid extension 
   char* file = argv[1];
   char* save_ptr;
   char* extension = strtok_r(argv[1], ".", &save_ptr);
   if (strcmp(extension,  "straight") != 0) {
        perror("Invalid file, must be .straight file");
	return EXIT_FAILURE;
   }

   // Lexical Analysis
   Lexer lexer = make_lexer();
   FILE* fd = fopen(file, "r");
   
   lexer = read_tokens(lexer, fd);
     
   fclose(fd);

   printf("%d", is_queue_empty(lexer));

   return EXIT_SUCCESS;
}

