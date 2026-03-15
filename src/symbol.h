#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "util.h"

#define DEFAULT_LOAD_THRESHOLD 0.75
#define DEFAULT_CAPACITY 11
#define NOT_FOUND -1
#define HASH_CONSTANT 39

// View as bucket for typical hash table

struct SymbolEntry_ {
     string id;
     int num;
     struct SymbolEntry_* next_item;
 };

typedef struct SymbolEntry_* SymbolEntry;

// Hash table definition
struct HashTable_ {
  SymbolEntry* data;
  size_t capacity;
  size_t size;
};

typedef struct HashTable_* HashTable;

SymbolEntry make_new_entry(string id, int num);

HashTable make_new_hash_table(size_t capacity);
int is_empty(HashTable table);
HashTable resize(HashTable old_table, size_t new_capacity);


int hash(string key, HashTable table);
int lookup(string id, HashTable table);

HashTable update(string id, int value, HashTable table);


#endif
