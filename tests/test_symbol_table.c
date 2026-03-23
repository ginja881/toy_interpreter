#include "symbol.h"
#include "util.h"
#include <time.h>
int main(int argc, char** argv) {
      if (argc < 2) {
          perror("\nMust specify capacity\n");
	  _Exit(-1);
      }
      srand(time(NULL));
     
      size_t capacity = atoi(argv[1]);
      
      HashTable hash_table = make_new_hash_table(capacity);

      printf("\n Testing for emptiness\n");
      assert(is_empty(hash_table));

      printf("\n Passed!\n");

      char* key_input = "abcdefghijklmnopqrstuvwxyz";
      
      printf("\n ---SYMBOL UPDATE and LOOKUP---\n");

      for (size_t i = 0; key_input[i] != '\0'; i++) {
            char input[1];
	    input[0] = key_input[i];
	    input[1] = '\0';

            string actual_key = String(input);

            printf("\nTesting update on key: %s\n", actual_key);
	    
	    hash_table = update(actual_key, rand(), hash_table);
	    assert(hash_table);

	    printf("\n Testing lookup on same key\n");
            int value = lookup(actual_key, hash_table);

	    if (value == NOT_FOUND)
	       printf("\n Value at %s is not found\n", actual_key);
	    else
	       printf("\n Value at %s is %d\n", actual_key, value);

	    printf("\nSUCCESS\n");
      }
      
     

}
