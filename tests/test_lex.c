#include "lex.h"
#include "util.h"

int main(void) {
    Lexer lexer = make_lexer();
    FILE* fd = fopen("tests/source_files/first.straight", "r");
    read_tokens(lexer, fd);

    while (is_queue_empty(lexer) != TRUE) {
         RawToken raw_token = eat_token(lexer);
         assert(raw_token);
         
	 
	 printf("\n Token type: \"%d\" \n", token_type);
	 printf("\n Token text:  \"%s\" \n", raw_token->text);
	 printf("\n Token size: %ld \n", raw_token->text_size);
    }

    return EXIT_SUCCESS;
}
