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
      
      for (size_t i = 0; i < old_table->capacity; i++) {
            SymbolEntry current = old_table->data[i];
	    while (current != NULL) {
	          new_table = update(current->id, current->num, new_table);
		  current = current->next_item;
	    }
      }
      

      free(old_table->data);
      free(old_table);

      new_table->capacity = new_capacity;
      
      return new_table;
}

int hash(string key, HashTable table) {
     
     
      size_t string_size = strlen(key);
      int hash_code = 0;
      for (size_t i = 0; i < string_size; i++) {
          
	  hash_code += (hash_code * HASH_CONSTANT + (unsigned long)key[i]) % (table->capacity);
      }     
      return (int)((hash_code));
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
    
     if (symbol_entry == NULL) {
         
         table->data[location] = make_new_entry(id, value);
	 
	 table->size++;
	 return table;
     }
    
     while (1) {
          if (strcmp(symbol_entry->id, id) == 0) {
	       symbol_entry->num = value;
	       return table;
	  }
           
	  if (symbol_entry->next_item == NULL) {
	     
	      symbol_entry->next_item = make_new_entry(id, value);
	      
	      table->size++;
	      return table;
	  }
	  symbol_entry = symbol_entry->next_item;
     }
     
     
    

     return table;
}
