#include "hash_functions.hpp"

#include <stdint.h>
#include <string.h>
#include <nmmintrin.h>

#include "hash_table.hpp"

int HashConstant(HashTableKey /*key*/) {
    return 0;
}

int HashSum(HashTableKey key) {
    int hash = 0;
    while (*key != '\0') {
        hash += (int)(*key++);
    }
    return hash;
}

int HashLength(HashTableKey key) {
    return (int)strlen(key);
}

int HashPolynomial(HashTableKey key) {
    int hash = 0;
    int p = 31;

    while (*key != '\0') {
        hash = (hash * p + (int)(*key++)) % (__INT_MAX__ / 2);
    }

    return hash;
}

int HashDJB2(HashTableKey key) {
    unsigned int hash = 5381;
    int c = 0;

    while ((c = (unsigned char)*key++) != '\0') {
        hash = hash * 33 + (unsigned int)c;
    }

    return (int)hash;
}

int HashFNV1a(HashTableKey key) {
    unsigned int hash = 2166136261u;

    while (*key != '\0') {
        hash ^= (unsigned char)(*key++);
        hash *= 16777619u;
    }

    return (int)hash;
}

int HashCRC32(HashTableKey key) {
    uint32_t crc = 0xFFFFFFFF;

    while (*key != '\0') {
        crc = _mm_crc32_u8(crc, (uint8_t)*key++);
    }

    return (int)(crc ^ 0xFFFFFFFF);
}
