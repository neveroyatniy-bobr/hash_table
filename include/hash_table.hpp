#ifndef HASH_TABLE_HPP_
#define HASH_TABLE_HPP_

#include <stdlib.h>

#include "hash_table_elem.hpp"
#include "vector.hpp"

typedef int (*HashFunc)(HashTableKey);

static const size_t BUCKETS_COUNT = 100;

struct HashTable {
    Vector buckets[BUCKETS_COUNT];
    HashFunc HashFunc;
};

HashTable HashTableInit(HashFunc HashFunc);

HashTableValue HashTableLookup(HashTable* hash_table, HashTableKey key, HashTableValue value);

#endif // HASH_TABLE_HPP_