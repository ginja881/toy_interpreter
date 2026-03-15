#include "lex.h"

TokenQueue make_token_queue(void) {
        /*
	 * @brief constructor for token stream
	 */
        TokenQueue new_queue = (TokenQueue)checked_malloc(sizeof(struct TokenQueue_));
	new_queue->token_head = (RawToken*) checked_malloc(sizeof(struct RawToken_));
        new_queue->token_tail = &new_queue->token_head;
	new_queue->size = 0;
	
	return new_queue;
}

int is_empty(TokenQueue queue) {
     return queue->size == 0 ? TRUE : FALSE;
}


TokenQueue enqueue(TokenQueue queue, RawToken new_token) {
     
      queue->size++;
      if (queue.is_empty() == TRUE) {
           queue->token_head = &new_token;
	   queue->token_tail = &queue->token_head;
	   
	   return;
      }


      queue->token_tail->next = new_token;
      quueue->token_tail = queue->token_tail->next;
      return queue;
}

RawToken dequeue(TokenQueue queue) {
       
       if (queue.is_empty() == TRUE) {
            perror("TOKEN QUEUE EMPTY");
	    return NULL;
       }

       queue->size--;
       RawToken 
}

