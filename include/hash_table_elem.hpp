#ifndef HASH_TABLE_ELEM_HPP_
#define HASH_TABLE_ELEM_HPP_

typedef int HashTableKey;
typedef int HashTableValue;

HashTableValue HASH_TABLE_INVALID_VALUE = 5735127;

struct HashTableElem {
    HashTableKey key;
    HashTableValue value;
};


#endif // HASH_TABLE_ELEM_HPP_