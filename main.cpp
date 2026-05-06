#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hash_table.hpp"
#include "hash_functions.hpp"

const size_t MAX_BUFFER_SIZE = 10 * 1024 * 1024;
const size_t MAX_WORDS_COUNT = 1000000;

static char file_buffer[MAX_BUFFER_SIZE] = {};
static const char* words_pointers[MAX_WORDS_COUNT] = {};
static size_t words_count = 0;

struct HashTest {
    hash_func_t func;
    const char* csv_file_name;
};

int PrepareData(const char* input_file_name);

int RunTest(const HashTest test);

int main() {
    const char* input_file = "text.txt";

    PrepareData(input_file);
    if (words_count == 0) {
        return 1;
    }

    HashTest test = { HashCRC32, "data/stats_crc32.csv" };

    printf("Выполняется %s\n.", test.csv_file_name);
    RunTest(test);

    printf("Готово.\n");

    return 0;
}


int PrepareData(const char* input_file_name) {
    FILE* input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Не удалось открыть входной файл\n");
        return -1;
    }

    size_t bytes_read = fread(file_buffer, 1, MAX_BUFFER_SIZE - 1, input_file);
    file_buffer[bytes_read] = '\0';
    fclose(input_file);

    bool in_word = false;

    for (size_t i = 0; i < bytes_read; i++) {
        if (isalpha(file_buffer[i])) {
            file_buffer[i] = (char)tolower(file_buffer[i]);
            if (!in_word) {
                if (words_count < MAX_WORDS_COUNT) {
                    words_pointers[words_count++] = &file_buffer[i];
                }
                in_word = true;
            }
        } 
        else {
            file_buffer[i] = '\0';
            in_word = false;
        }
    }

    return 0;
}

int RunTest(const HashTest test) {
    HashTable hash_table = HashTableInit(test.func);

    for (size_t i = 0; i < words_count; i++) {
        const char* current_word = words_pointers[i];
        
        HashTableValue current_count = HashTableGet(&hash_table, current_word);
        
        if (current_count == HASH_TABLE_INVALID_VALUE) {
            HashTableSet(&hash_table, current_word, 1); 
        } 
        else {
            HashTableSet(&hash_table, current_word, current_count + 1);
        }
    }

    FILE* csv_file = fopen(test.csv_file_name, "w");

    if (csv_file == NULL) {
        fprintf(stderr, "Не удалось создать csv файл");
        return -1;
    }

    fprintf(csv_file, "BucketIndex,Count\n");

    for (size_t i = 0; i < BUCKETS_COUNT; i++) {
        fprintf(csv_file, "%lu,%lu\n", i, VectorGetSize(&hash_table.buckets[i]));
    }

    fclose(csv_file);

    HashTableDestroy(&hash_table);

    return 0;
}