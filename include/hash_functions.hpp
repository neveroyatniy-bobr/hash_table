#ifndef HASH_FUNCTIONS_HPP_
#define HASH_FUNCTIONS_HPP_

#include "hash_functions.hpp"

#include <string.h>

#include "hash_table.hpp"

int HashConstant(HashTableKey key);

int HashSum(HashTableKey key);

int HashLength(HashTableKey key);

int HashPolynomial(HashTableKey key);

int HashDJB2(HashTableKey key);

int HashFNV1a(HashTableKey key);

int HashCRC32(HashTableKey key);

#endif // HASH_FUNCTIONS_HPP_