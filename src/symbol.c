#include "symbol.h"

SymbolEntry make_new_entry(string id, int num) {
    SymbolEntry symbol_entry = (SymbolEntry)checked_malloc(sizeof(struct SymbolEntry_));
   
    symbol_entry->id = strdup(id);
    symbol_entry->num = num;
    symbol_entry->next_item = NULL;
    
    return symbol_entry;
}
HashTable make_new_hash_table(size_t capacity) {
       HashTable hash_table = (HashTable) checked_malloc(sizeof(struct HashTable_));
       SymbolEntry* bucket_array = (SymbolEntry*) checked_malloc(sizeof(struct  SymbolEntry_) * capacity);
       for (size_t i = 0; i < capacity; i++)
           bucket_array[i] = NULL;

       hash_table->data = bucket_array;
       hash_table->size  = 0;
       hash_table->capacity = capacity;

       return hash_table;
}


int is_empty(HashTable table) {
    return (table->size == 0 ) ? TRUE : FALSE;
}

HashTable resize(HashTable old_table, size_t new_capacity) {
      assert(old_table);
     
      HashTable new_table = make_new_hash_table(new_capacity);
      
      assert(new_table);
      printf("work");
      for (size_t i = 0; i < old_table->capacity; i++) {
            SymbolEntry current = old_table->data[i];
	    while (current != NULL) {
	          new_table = update(current->id, current->num, new_table);
		  current = current->next_item;
	    }
      }
      new_table->size = old_table->size;

      free(old_table->data);
      free(old_table);

      new_table->capacity = new_capacity;
      
      return new_table;
}

int hash(string key, HashTable table) {
     
     
      int hash_code = 0;
      for (size_t i = 0; i < sizeof(key); i++) {
            int current_ascii = (int)key[i];
	   
            hash_code += current_ascii * i * HASH_CONSTANT;
      }
      return hash_code % (table->capacity);
}

int lookup(string key, HashTable table) { 

      int location = hash(key, table);
      SymbolEntry symbol_entry = table->data[location];
       
      while (symbol_entry != NULL) {
          if (strcmp(symbol_entry->id, key) == 0)
	      return symbol_entry->num;
	  symbol_entry = symbol_entry->next_item;
      }
      return NOT_FOUND;

      
}

HashTable update(string id, int value, HashTable table) {
     
     if ((double)table->size/table->capacity >= DEFAULT_LOAD_THRESHOLD)
        table = resize(table, table->capacity*2);
     int location = hash(id, table);
     SymbolEntry symbol_entry = table->data[location];
    
    
     while (symbol_entry != NULL) {
          if (strcmp(symbol_entry->id, id) == 0) {
	       symbol_entry->num = value;
	       return table;
	  }

	  if (symbol_entry->next_item == NULL) {
	       symbol_entry->next_item = make_new_entry(id, value);
	       table->size++;
	       return table;
	  }
	  else
	      symbol_entry = symbol_entry->next_item;
     }
     
     table->data[location] = make_new_entry(id, value);
     table->size++;

     return table;
}
