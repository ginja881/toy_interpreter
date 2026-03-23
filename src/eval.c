#include "eval.h"

ExpressionResult interpExp(A_Exp exp, HashTable symbol_table) {
       /*
	* @brief evaluator for expressions
	* @param exp A_Exp object
	*/

        
        ExpressionResult result;
        result.table = symbol_table;

       

        if (exp->kind == Num_Exp)
	   result.val = exp->u.num_exp.num;
	else if (exp->kind == ID_Exp)
	    result.val = lookup(exp->u.id_exp.id, result.table);
	else if (exp->kind == Op_Exp) {
	      A_Exp left = exp->u.op_exp.exp1;
	      A_Exp right = exp->u.op_exp.exp2;
                                                  
	      ExpressionResult left_result = interpExp(left, result.table);
	      ExpressionResult right_result = interpExp(right, left_result.table);
	      result.table = right_result.table;
	      symbol_table = result.table;
	      BinOp operator = exp->u.op_exp.op;

	      switch (operator) {
	          case OP_ADD:
		      result.val = left_result.val +  right_result.val;
		      break;
		  case OP_SUB:
		      result.val = left_result.val - right_result.val;
		      break;
		  case OP_MUL:
		      result.val = left_result.val * right_result.val;
		      break;
		  case OP_DIV:
		      result.val = (int)(left_result.val / right_result.val);
		      break;
	      }
	}
	else if (exp->kind == Eseq_Exp) {
           
	     A_Stm eseq_stm = exp->u.eseq_exp.stm;
             
             result.table = interpStatement(eseq_stm, result.table);

	     ExpressionResult eseq_exp_result = interpExp(
	     	exp->u.eseq_exp.exp, 
	        result.table
	     );

	    
	     result.table = eseq_exp_result.table;
	     symbol_table = result.table;
	     result.val = eseq_exp_result.val;
	    
	}
        return result;
}

HashTable interpExpList(A_ExpList exp_list, HashTable symbol_table, int print) {
       /*
	* @brief evaluator for expresion lists.
	* @param exp_list A_ExpList object
	*/
        A_ExpList current_exp_list_node = exp_list;
	while (current_exp_list_node != NULL) {
             A_Exp current_exp = current_exp_list_node->exp;
	     ExpressionResult current_exp_result = interpExp(current_exp, symbol_table);
	     symbol_table = current_exp_result.table;
	     
	     if (print == TRUE)
	         printf("\n %d \n", current_exp_result.val);
	     current_exp_list_node = current_exp_list_node->tail;
	}

	return symbol_table;
}

HashTable interpStatement(A_Stm statement, HashTable symbol_table) {
       /*
	* @brief evaluator for statements 
	* @param statement A_Stm object
	*/
       
	if(statement->kind == ExpStm) {
	     ExpressionResult result = interpExp(
	     	statement->u.expression_stm.exp, 
		symbol_table
	     );
             symbol_table = result.table;
	     
	}
	else if (statement->kind == AssignStm) {
	     string id = statement->u.assign_stm.id;
	     ExpressionResult result = interpExp(
	          statement->u.assign_stm.exp,
		  symbol_table
	     );
           
	     symbol_table = update(id, result.val, result.table);
	    
	}
	else if (statement->kind == PrintStm) {
	     A_ExpList expression_list = statement->u.print_stm.exp_list;
	     symbol_table = interpExpList(expression_list, symbol_table, TRUE);
	     
	}
        
        return symbol_table;
}

HashTable interpProgram(A_Stm AST_Root, HashTable symbol_table) {
      /*
       * @brief main evaluator for program. runtime is sum of runtimes that each state takes.
       * @param AST_Root root of AST made by parser
       */
       

       if (AST_Root == NULL) return symbol_table;

       switch(AST_Root->kind) {
            case CompoundStm:
	        symbol_table = interpProgram(AST_Root->u.compound_stm.stm1, symbol_table);
		return interpProgram(AST_Root->u.compound_stm.stm2, symbol_table);
	    default:
	        break;
       }
       return interpStatement(AST_Root, symbol_table);
       
       return interpStatement(AST_Root, symbol_table);
}
