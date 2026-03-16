#include "lex.h"

Lexer make_lexer(void) {
      Lexer lexer = (Lexer)checked_malloc(sizeof(struct Lexer_));
      lexer->queue = (TokenQueue)checked_malloc(sizeof(struct TokenQueue_));

      lexer->queue->token_head = NULL;
      lexer->queue->token_tail = lexer->queue->token_head;

      lexer->queue->size = 0;

      lexer->pos = 0;
      return lexer;
}

int is_queue_empty(Lexer lexer) {
    return (lexer->queue->size == 0 ? TRUE : FALSE);
}

Lexer enqueue_token(Lexer lexer, RawToken token) {
    
    if (is_queue_empty(lexer) == TRUE) {
        lexer->queue->token_head = token;
	lexer->queue->token_tail = lexer->queue->token_head;
    }
    else {
        
        lexer->queue->token_tail->next = token;
        lexer->queue->token_tail = lexer->queue->token_tail->next;
    }
    lexer->queue->size++;
    return lexer;
}

RawToken dequeue_token(Lexer lexer) {
    if (is_queue_empty(lexer) == TRUE) {
        perror("\nLexer tried dequeuing while empty\n");
	return NULL;
    }
    RawToken old_head = lexer->queue->token_head;
    if (lexer->queue->size > 1) {
       lexer->queue->token_head = lexer->queue->token_head->next;
       
    }
    else {
       lexer->queue->token_head = NULL;
       lexer->queue->token_tail = lexer->queue->token_head;
    }
    lexer->queue->size--;
    return old_head;
}



Lexer read_tokens(Lexer lexer, FILE* fd) {
     char* input;
     size_t size = 0;
     getline(&input, &size, fd);
    
     while(input[lexer->pos] != '\0') {
           char current_char = input[lexer->pos];
           if (isspace(current_char) || current_char == ',') {
	       lexer->pos++;
	       continue;
	   }

           char* lexeme = (char*)checked_malloc(100);

	   RawToken new_token = (RawToken) checked_malloc(sizeof(struct RawToken_));
           new_token->next = NULL;
	   new_token->text_size = 1;
           lexeme[0] = current_char;
           // DRY chain for operators, parentheses, and semicolons
           if (current_char == '(') {
	       new_token->token = L_PAREN;
	       lexer->pos++;
	   }
	   else if (current_char == ')') {
	       new_token->token = R_PAREN;
	       lexer->pos++;
	   }
	   else if (current_char == '+') {
	       new_token->token = PLUS;
	       lexer->pos++;
	   }
	   else if (current_char == '-') {
	       new_token->token = SUB;
	       lexer->pos++;
	   }
	   else if (current_char == '*') {
	       new_token->token = MUL;
	       lexer->pos++;
	   }
	   else if (current_char == ';') {
	       new_token->token = SEMI_COLON;
	       lexer->pos++;
	   }
	   else if (current_char == '/') {
	       new_token->token = DIV;
	       lexer->pos++;
	   }
	   else if (current_char == '%') {
	       new_token->token = MOD;
	       lexer->pos++;
	   }
           // IDs, print statements, and numbers
           else if (isalnum(current_char)) {
	       Token token_type = NUM;

               int i = 0;	      
	       for (; isalnum(current_char) && i <=99 ; i++) {
	            if (isalpha(current_char))
		       token_type = ID;
		    lexeme[i] = input[lexer->pos];
		    lexer->pos++;
		    current_char = input[lexer->pos];
	                     	    
	       }
	       new_token->text_size = i;
	       lexeme[new_token->text_size] = '\0';
	       if (i == 5&& strncmp(lexeme, "print", 5) == 0)
	           token_type = PRINT;
	
	       new_token->token = token_type;
	   }
	   else if (current_char == ':') {
	      
	      if ((lexer->pos + 1) > size) 
	         error(SYNTAX_ERROR, lexer->pos);
	      else if (input[lexer->pos + 1] == '=') {
	           new_token->token = ASSIGN;
		   lexeme[1] = '=';
		   new_token->text_size++;
		   lexer->pos += 2;
              }
              else
	          error(SYNTAX_ERROR, lexer->pos);
	           
	   }
	   else 
	      error(INVALID_CHARACTER, lexer->pos);
           lexeme[new_token->text_size] = '\0';
           new_token->text = String(lexeme);

    
	   enqueue_token(lexer, new_token);
	  
     }

     free(input);
     return lexer;
}
