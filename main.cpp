#include <stdlib.h>
#include <time.h>

#include "hash_table.hpp"

int HashFunc(HashTableKey key);

int HashFunc(HashTableKey key) {
    return key%(int)BUCKETS_COUNT;
}

int main() {
    srand((unsigned int)time(NULL));

    HashTable hash_table = HashTableInit(HashFunc);

    for (int i = 0; i < 1000; i++) {
        if (HashTableSet(&hash_table, i, rand()) != 0) {
        }
    }

    HashTableDump(&hash_table);

    int err = HashTableDestroy(&hash_table);
    printf("%d\n", err);

    return 0;
}