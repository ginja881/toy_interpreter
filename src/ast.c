#include "ast.h"

A_Stm compound_stm(A_Stm stm1, A_Stm stm2) {
   /* 
    * @brief constructor for compound statement
    * @param stm1 first statement for compound statement
    * @param stm2 second statement for compound statement
    */
   A_Stm new_stm = (A_Stm) checked_malloc(sizeof(struct A_Stm_));
   new_stm->kind = CompoundStm;

   new_stm->u.compound_stm.stm1 = stm1;
   new_stm->u.compound_stm.stm2 = stm2;
   
   return new_stm;
}

A_Stm print_stm(A_ExpList exp_list) {
   /*
    * @brief constructor for print statements
    * @param exp_list expression list for print statement
    */

   A_Stm new_stm = (A_Stm) checked_malloc(sizeof(struct A_Stm_));
   new_stm->kind = PrintStm;

   new_stm->u.print_stm.exp_list = exp_list;
   
   return new_stm;
}

A_Stm assign_stm(string id, A_Exp exp) {
   /*
    * @brief constructor for assignment statements
    * @param id identifier for variable for assignment
    * @param exp expression to make value to be stored in id variable
    */ 

   A_Stm new_stm =(A_Stm) checked_malloc(sizeof(struct A_Stm_));
  
   new_stm->kind = AssignStm;

   new_stm->u.assign_stm.id = strdup(id);
   new_stm->u.assign_stm.exp = exp;
   
  
   return new_stm;
}

A_Stm expression_stm(A_Exp exp) {
      /*
       * @brief constructor for expression statements
       * @param exp expression for expression statement
       */

       A_Stm new_stm = (A_Stm) checked_malloc(sizeof(struct A_Stm_));
       new_stm->kind = ExpStm;
      
       new_stm->u.expression_stm.exp = exp;
       return new_stm;
}

A_Exp id_exp(string id) {
    /*
     * @brief constructor for id expressions
     * @param id identifier for variable with identifier of "id"
     */

    A_Exp new_exp = (A_Exp) checked_malloc(sizeof(struct A_Exp_));
    new_exp->kind = ID_Exp;

    new_exp->u.id_exp.id = strdup(id);
    
    return new_exp;
}

A_Exp num_exp(int num) {
   /*
    * @brief constructor for numerical expressions
    * @param num numerical value of numerical expression
    */

   A_Exp new_exp = (A_Exp) checked_malloc(sizeof(struct A_Exp_));
   new_exp->kind = Num_Exp;

   new_exp->u.num_exp.num = num;

  
   return new_exp;
}

A_Exp eseq_exp(A_Stm stm, A_Exp exp) {
   /*
    * @brief  constructor for expression sequence
    * @param stm statement for expression sequence 
    * @param exp expression for expression sequence
    */

   A_Exp new_exp =(A_Exp) checked_malloc(sizeof(struct A_Exp_));
   new_exp->kind = Eseq_Exp;
   
   new_exp->u.eseq_exp.stm = stm;
   new_exp->u.eseq_exp.exp = exp;
   
   return new_exp;
}

A_Exp op_exp(A_Exp exp1, BinOp op, A_Exp exp2) {
  /*
   * @brief constructor for operation expressions
   * @param exp1 first expression for operation expression
   * @param exp2 second expression for operation expression
   * @param op operator enum
   */

  A_Exp new_exp = (A_Exp) checked_malloc(sizeof(struct A_Exp_));
  new_exp->kind = Op_Exp;
 
  new_exp->u.op_exp.exp1 = exp1;
  new_exp->u.op_exp.exp2 = exp2;
  new_exp->u.op_exp.op = op;

  return new_exp;
}

A_ExpList exp_list(A_Exp exp) {
    /*
     * @brief constructor for expression list
     * @param exp expression for expression list
     */

    A_ExpList new_explist = (A_ExpList) checked_malloc(sizeof(struct A_ExpList_));
    new_explist->exp = exp;
    new_explist->tail = NULL;

    return new_explist;
}

// Miscellaneous functions

int max_args_stm(A_Stm stm) {
     if (stm == NULL)
        return -1;
     
     if (stm->kind == PrintStm) {
        return max_args_exp(stm->u.print_stm.exp_list);
     }
     return -1; 
}
int max_args_exp(A_ExpList exp_list) {
    if (exp_list == NULL)
       return 0;

    A_Exp exp = exp_list->exp;
    assert(exp);

    if (exp->kind == Eseq_Exp && exp->u.eseq_exp.stm != NULL) {
         return 1 + max(max_args_stm(exp->u.eseq_exp.stm), max_args_exp(exp_list->tail));
    }
    return 1 + max_args_exp(exp_list->tail);
   
}

// Recursive Descent
BinOp get_op(Token operator) {
    if (operator == PLUS)
       return OP_ADD;
    else if (operator == SUB)
       return OP_SUB;
    else if (operator == MUL)
       return OP_MUL;
    return OP_DIV;
}

int match(Token token_type, Lexer lexer) {
      /*
       * @brief matching for parser
       * @param token_type type of token
       * @param lexer lexical analyzer object
       */
      if (peek(lexer) == NULL) return FALSE;
      return (peek(lexer)->token == token_type ? TRUE : FALSE);
}
A_Exp parse_literal(Lexer lexer) {
       A_Exp exp = NULL;
       
       RawToken current_token = peek(lexer);
       if (match(ID, lexer) == TRUE) {
           exp = id_exp(current_token->text);
	   eat_token(lexer);
      }
       else if (match(NUM, lexer) == TRUE) {
           exp = num_exp(atoi(current_token->text));
	   eat_token(lexer);
       }
       else if (match(L_PAREN, lexer) == TRUE) {
            eat_token(lexer);
	    exp = parse_expression(lexer);
	    if (match(R_PAREN, lexer) == FALSE) {
	       current_token = peek(lexer);
	       error(SYNTAX_ERROR, current_token->pos, current_token->text, current_token->line_pos);
	    }
	    eat_token(lexer);

       }
       else
           error(SYNTAX_ERROR, current_token->pos, current_token->text, current_token->line_pos);
       return exp;

}

A_Exp parse_factor(Lexer lexer) {
      A_Exp left = parse_literal(lexer);
      while (match(PLUS, lexer) == TRUE || match(SUB, lexer) == TRUE) {
           RawToken current_token = eat_token(lexer);
           BinOp operator = get_op(current_token->token);
	   A_Exp right = parse_expression(lexer);
           left = op_exp(left, operator, right);
      }
      return left;
}

A_Exp parse_term(Lexer lexer) {
     A_Exp left = parse_factor(lexer);
     while (match(MUL, lexer) == TRUE || match(DIV, lexer) == TRUE) {
         RawToken current_token = eat_token(lexer);
	 BinOp operator = get_op(current_token->token);
	 A_Exp right = parse_expression(lexer);
	 left = op_exp(left, operator, right);
     }
     return left;
}

int check_next_stm(Lexer lexer) {
      RawToken current_token = peek(lexer);
      switch (current_token->token) {
          case ID:
	  case NUM:
	  case PRINT:
	  case L_PAREN:
	      return TRUE;
	  default:
	      break;
      }
      return FALSE;
}

A_Exp parse_expression(Lexer lexer) {
     
     if (match(L_PAREN, lexer) == TRUE) {
	  eat_token(lexer);
	  if (check_next_stm(lexer) == TRUE) {
	       A_Stm eseq_stm = parse_statement(lexer);
	       
	       if (match(COMMA, lexer) == TRUE) {
	           
	            eat_token(lexer);
	           
                    A_Exp eseq_expression = parse_expression(lexer);
	            if (match(R_PAREN, lexer) == FALSE)
	               error(SYNTAX_ERROR, peek(lexer)->pos, peek(lexer)->text, peek(lexer)->line_pos);
	            eat_token(lexer);
	            return eseq_exp(eseq_stm, eseq_expression);
	       }
	       else {
	           if (match(R_PAREN, lexer) == FALSE)
		      error(SYNTAX_ERROR, peek(lexer)->pos, peek(lexer)->text, peek(lexer)->line_pos);
		   eat_token(lexer);
		   return eseq_exp(eseq_stm, num_exp(0));
	       }
	  }
          else {
              A_Exp expression = parse_expression(lexer);
	      if (match(R_PAREN, lexer) == FALSE)
	          error(SYNTAX_ERROR, peek(lexer)->pos, peek(lexer)->text, peek(lexer)->line_pos);
              eat_token(lexer);
	      return expression;
	  }  
     }
     return parse_term(lexer);
     
}
A_ExpList parse_expression_list(Lexer lexer) {
      
     
      A_ExpList head = NULL;
      A_ExpList current_node = head;
      while (is_queue_empty(lexer) != TRUE && match(R_PAREN, lexer) != TRUE) {
          if (head == NULL) {
	      head = exp_list(parse_expression(lexer));
	      current_node = head;
	  }
          else {
	     current_node->tail = exp_list(parse_expression(lexer));
	     current_node = current_node->tail;
	  }

	  if (match(COMMA, lexer) == TRUE)
	     eat_token(lexer);
	  else
	     break;
      }
      return head;
}
A_Stm parse_statement(Lexer lexer) {
     A_Stm main_stm = NULL;
     RawToken current_token = peek(lexer);
    
     if (current_token->token == PRINT) {
          eat_token(lexer);
          
	
	  if (is_queue_empty(lexer) == TRUE)
	     error(SYNTAX_ERROR, peek(lexer)->pos, peek(lexer)->text, peek(lexer)->line_pos); 
	  else if (peek(lexer)->token != L_PAREN)
	      error(SYNTAX_ERROR, peek(lexer)->pos, peek(lexer)->text, peek(lexer)->line_pos);


	  eat_token(lexer);
	  A_ExpList expression_list = parse_expression_list(lexer);
	  if (match(R_PAREN, lexer) == TRUE) {
	     eat_token(lexer);
	     main_stm = print_stm(expression_list);
	  }
	  else
	     error(SYNTAX_ERROR, peek(lexer)->pos, peek(lexer)->text, peek(lexer)->line_pos);
     }
     else if (current_token->token == ID) {
           string id = current_token->text;
	   eat_token(lexer);

	   if (is_queue_empty(lexer) == TRUE)
	      error(SYNTAX_ERROR, peek(lexer)->pos, peek(lexer)->text, peek(lexer)->line_pos);
	   else if (peek(lexer)->token !=ASSIGN)
	      error(SYNTAX_ERROR, peek(lexer)->pos, peek(lexer)->text, peek(lexer)->line_pos);

	   eat_token(lexer);
           
	   A_Exp main_exp = parse_expression(lexer);
	  
	   main_stm = assign_stm(id, main_exp);
     }
     else if (current_token->token == NUM || current_token->token == ID || current_token->token == L_PAREN) {
          A_Exp main_exp = parse_expression(lexer);
	  main_stm = expression_stm(main_exp);
     }
     else
         error(SYNTAX_ERROR, current_token->pos, current_token->text, current_token->line_pos);

     return main_stm;
}

A_Stm parse_source_code(Lexer lexer) {
      /*
       * @brief main parsing algorithm
       * @param lexer Lexical analyzer object
       */

      // Root and current_stm for tracking
      A_Stm root = NULL;
      A_Stm current_stm = NULL;
      
      // Sentinel for consuming/matching tokens
      RawToken current_token = peek(lexer);
      while (is_queue_empty(lexer) == FALSE && current_token->token != END_OF_FILE) {
               // Make STM
	       
               current_stm = parse_statement(lexer);
	       // Check for compound statement
	       current_token = peek(lexer);
	       	       
	       if (match(SEMI_COLON, lexer) == TRUE) {
	            eat_token(lexer);
		    // Root case
	            if (root == NULL)
		        root = current_stm;
		    else
		        root = compound_stm(root, current_stm);
	       }
	       else
	          error(SYNTAX_ERROR, current_token->pos, current_token->text, current_token->line_pos);
	       // Update reference to stream front
	       current_token = peek(lexer);
	      
      }
      return root;
}


