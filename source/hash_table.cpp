#include "hash_table.hpp"

#include <assert.h>

HashTable HashTableInit(hash_func_t HashFunc) {
    assert(HashFunc != NULL);

    HashTable hash_table = { .buckets = {}, 
                             .HashFunc = HashFunc 
                           };
    
    for (size_t bucket_i = 0; bucket_i < BUCKETS_COUNT; bucket_i++) {
        if (VectorInit(hash_table.buckets + bucket_i, 0, sizeof(HashTableElem)) != VECTOR_OK) {
            return {};
        }
    }
                    
    return hash_table;
}

int HashTableDestroy(HashTable* hash_table) {
    assert(hash_table != NULL);

    bool is_ok = true;

    for (size_t bucket_i = 0; bucket_i < BUCKETS_COUNT; bucket_i++) {
        VectorError free_err = VectorFree(hash_table->buckets + bucket_i);
        if (free_err != VECTOR_OK) {
            VectorPrintError(free_err);
            is_ok = false;
        }
    }

    hash_table->HashFunc = NULL;

    return is_ok ? 0 : -1;
}

HashTableValue HashTableGet(HashTable* hash_table, HashTableKey key) {
    assert(hash_table != NULL);

    int hash = hash_table->HashFunc(key);
    size_t bucket_i = (size_t)hash % BUCKETS_COUNT;

    Vector* bucket = hash_table->buckets + bucket_i;
    size_t bucket_size = VectorGetSize(bucket);

    for (size_t i = 0; i < bucket_size; i++) {
        HashTableElem elem = {};
        VectorError get_err = VectorGet(bucket, i, &elem);
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
    size_t bucket_i = (size_t)hash % BUCKETS_COUNT;

    Vector* bucket = hash_table->buckets + bucket_i;
    size_t bucket_size = VectorGetSize(bucket);

    for (size_t i = 0; i < bucket_size; i++) {
        HashTableElem elem = {};
        VectorError get_err = VectorGet(bucket, i, &elem);
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

int HashTableDump(HashTable* hash_table) {
    fprintf(stderr, "--------HASH-TABLE-DUMP-------------\n");
    for (size_t bucket_i = 0; bucket_i < BUCKETS_COUNT; bucket_i++) {
        fprintf(stderr, "%lu\n", VectorGetSize(hash_table->buckets + bucket_i));
    }

    return 0;
}