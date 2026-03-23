#include "util.h"
#include "lex.h"
#include "ast.h"
#include "symbol.h"
#include "eval.h"

int main(int argc, char** argv) {
   if (argc < 2) {
       perror("Need to specify .straight file");
       return EXIT_FAILURE;
   }
   
   // Checking if file has valid extension 
   string extension = strrchr(argv[1], '.');
   if (!extension) {
       perror("Must specify .straight file");
       return EXIT_FAILURE;
   }
   if (strcmp(extension + 1, "straight") != 0) {
       perror("Must specify .straight file");
       return EXIT_FAILURE;
   }
      

   // Lexical Analysis
   Lexer lexer = make_lexer();
   FILE* fd = fopen(argv[1], "r");
   
   char* input = NULL;
   size_t size = 0;
   size_t line_pos = 0;
   while (getline(&input, &size, fd) != -1) {
         line_pos++;
	 lexer->pos = 0;
         lexer = read_tokens(lexer, input, size, line_pos);
	 
   }
   free(input);
   RawToken EOF_Token = (RawToken) checked_malloc(sizeof(struct RawToken_));
   EOF_Token->token = END_OF_FILE;
   EOF_Token->text_size = 0;
   EOF_Token->next = NULL;

   enqueue_token(lexer, EOF_Token);

   fclose(fd);
   
   
   A_Stm AST_root = parse_source_code(lexer); 
   HashTable symbol_table = make_new_hash_table(DEFAULT_CAPACITY);
   
   symbol_table = interpProgram(AST_root, symbol_table);

   return EXIT_SUCCESS;
}

