#include "lex.h"
#include "ast.h"
#include "utils.h"
#include "symbol.h"


void interp_program(A_Stm ast_root);


int main(int argc, char** argv) {
   if (argc < 2) {
       perror("Need to specify .straight file");
       return EXIT_FAILURE;
   }

   char* extension = strtok_r(argv[1], '.');
   if (strcmp(extension,  "straight") != 0) {
        perror("Invalid file, must be .straight file")
	return EXIT_FAILURE;
   }


   return EXIT_SUCCESS;
}
