#include "lex.h"
#include "util.h"

int main(void) {
    Lexer lexer = make_lexer();
    FILE* fd = fopen("tests/source_files/first.straight", "r");
    
    char* input;
    size_t size;
    size_t line_pos = 0;

    while (getline(&input, &size, fd) != -1) {
          line_pos++;
          lexer = read_tokens(lexer, input, size, line_pos);
	  lexer->pos = 0;
    }
    
    free(input);
    while (is_queue_empty(lexer) != TRUE) {
         RawToken raw_token = eat_token(lexer);
         assert(raw_token);
         char* token_type;
	 switch(raw_token->token) {
	       case L_PAREN:
	           token_type = "L_PAREN";
		   break;
	       case R_PAREN:
	           token_type = "R_PAREN";
		   break;
	       case MUL:
	           token_type = "MUL";
	           break;
	       case SUB:
	           token_type = "SUB";
		   break;
	      case SEMI_COLON:
	           token_type = "SEMI_COLON";
		   break;
	      case PLUS:
	           token_type = "ADD";
		   break;
	      case PRINT:
	           token_type = "PRINT";
		   break;
	      case ASSIGN:
	           token_type = "ASSIGN";
		   break;
	      case NUM:
	           token_type = "NUM";
		   break;
	      case ID:
	           token_type = "ID";
		   break;
              case DIV:
	           token_type = "DIV";
		   break;
	      default:
	           break;
	 }
	 
	 printf("\n Token type: \"%s\" \n", token_type);
	 printf("\n Token text:  \"%s\" \n", raw_token->text);
	 printf("\n Token size: %ld \n", raw_token->text_size);
    }

    return EXIT_SUCCESS;
}
