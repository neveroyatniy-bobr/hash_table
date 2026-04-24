#ifndef HASH_TABLE_HPP_
#define HASH_TABLE_HPP_

#include <stdlib.h>

#include "hash_table_elem.hpp"
#include "vector.hpp"

typedef int (*hash_func_t)(HashTableKey);

static const size_t BUCKETS_COUNT = 100;

struct HashTable {
    Vector buckets[BUCKETS_COUNT];
    hash_func_t HashFunc;
};

HashTable HashTableInit(hash_func_t HashFunc);
int HashTableDestroy(HashTable* hash_table);
HashTableValue HashTableGet(HashTable* hash_table, HashTableKey key);
int HashTableSet(HashTable* hash_table, HashTableKey key, HashTableValue value);
int HashTableDump(HashTable* hash_table);

#endif // HASH_TABLE_HPP_