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

   new_stm->u.assign_stm.id = id;
   new_stm->u.assign_stm.exp = exp;
   
  
   return new_stm;
}

A_Exp id_exp(string id) {
    /*
     * @brief constructor for id expressions
     * @param id identifier for variable with identifier of "id"
     */

    A_Exp new_exp = (A_Exp) checked_malloc(sizeof(struct A_Exp_));
    new_exp->kind = ID_Exp;

    new_exp->u.id_exp.id = id;
    
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


