#include "symbol.h"
#include "util.h"
int main(int argc, char** argv) {
      if (argc < 2) {
          perror("Must specify capacity");
	  return EXIT_FAILURE;
      }

     
      size_t capacity = atoi(argv[1]);
      
      HashTable hash_table = make_new_hash_table(capacity);

      printf("\n Testing for emptiness\n");
      assert(is_empty(hash_table));

      printf("\n Passed!\n");

      hash_table = update("a", 5, hash_table);
      hash_table = update("b", 2, hash_table);
      hash_table = update("c", 4, hash_table);


      printf("\n Testing updating\n");
      assert(hash_table);

      printf("\n Passed!\n");

      printf(
           "\n Grabbed pair with key %s and value %d \n", "a", 
           lookup("a", hash_table)
      );

      printf(
          "\n Grabbed pair with key %s and value %d \n", "b",
	  lookup("b", hash_table)
      );

      printf(
          "\n Grabbed pair with key %s and value %d \n", "c",
	  lookup("c", hash_table)
      );


}
