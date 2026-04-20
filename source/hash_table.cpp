#include "hash_table.hpp"

#include <assert.h>

HashTable HashTableInit(HashFunc HashFunc) {
    HashTable hash_table = { .buckets = {}, 
                             .HashFunc = HashFunc 
                           };
    
    for (int bucket_i = 0; bucket_i < BUCKETS_COUNT; bucket_i++) {
        if (VectorInit(hash_table.buckets + bucket_i, 0, 0) != VECTOR_OK) {
            return {};
        }
    }
                    
    return hash_table;
}

int HashTableDestroy(HashTable* hash_table) {
    for (int bucket_i = 0; bucket_i < BUCKETS_COUNT; bucket_i++) {
        if (VectorFree(hash_table->buckets + bucket_i) != VECTOR_OK) {
            return -1;
        }
    }

    hash_table->HashFunc = NULL;

    return 0;
}

HashTableValue HashTableGet(HashTable* hash_table, HashTableKey key) {
    assert(hash_table != NULL);

    int hash = hash_table->HashFunc(key);
    int bucket_i = hash % BUCKETS_COUNT;

    Vector* bucket = hash_table->buckets + bucket_i;
    size_t bucket_size = VectorGetSize(bucket);

    for (int i = 0; i < bucket_size; i++) {
        HashTableElem elem = {};
        VectorError get_err = VectorGet(bucket, bucket_i, &elem);
        if (get_err != VECTOR_OK) {
            return HASH_TABLE_INVALID_VALUE;
        }

        if (elem.key == key) {
            return elem.value;
        }
    }

    return HASH_TABLE_INVALID_VALUE;
}

int HashTableSet(HashTable* hash_table, HashTableKey key, HashTableValue value) {
    assert(hash_table != NULL);

    int hash = hash_table->HashFunc(key);
    int bucket_i = hash % BUCKETS_COUNT;

    Vector* bucket = hash_table->buckets + bucket_i;
    size_t bucket_size = VectorGetSize(bucket);

    for (int i = 0; i < bucket_size; i++) {
        HashTableElem elem = {};
        VectorError get_err = VectorGet(bucket, bucket_i, &elem);
        if (get_err != VECTOR_OK) {
            return -1;
        }

        if (elem.key == key) {
            VectorError set_err = VectorSet(bucket, bucket_i, &value);
            return set_err == VECTOR_OK ? 0 : -1;
        }
    }

    HashTableElem new_elem = {key, value};
    VectorError push_err = VectorPush(bucket, &new_elem);
    return push_err == VECTOR_OK ? 0 : -1;
}