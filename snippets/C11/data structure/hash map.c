#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_CAPACITY 16
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct HashTableEntry {
    const char* key;
    void* value;
} HashTableEntry;

typedef struct HashTable {
    HashTableEntry* entries;
    size_t capacity;
    size_t length;
} HashTable;

HashTable* HashTable__init__(void);
void HashTable__del__(HashTable* table);
void* HashTable_get(HashTable* table, const char* key);
const char* HashTable_set(HashTable* table, const char* key, void* value);
size_t HashTable_length(HashTable* table);

HashTable* HashTable__init__(void) {
    HashTable* table = malloc(sizeof(HashTable));
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;
    table->entries = calloc(table->capacity, sizeof(HashTableEntry));
    return table;
}

void HashTable__del__(HashTable* table) {
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].key != NULL) free((void*)table->entries[i].key);
    }
    free(table->entries);
    free(table);
}

static uint64_t gen_hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

void* HashTable_get(HashTable* table, const char* key) {
    uint64_t hash = gen_hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

    while (table->entries[index].key != NULL) {
        if (strcmp(key, table->entries[index].key) == 0) {
            return table->entries[index].value;
        }
        index++;
        if (index >= table->capacity) index = 0;
    }
    return NULL;
}

static const char* HashTable_set_entry(HashTableEntry* entries, size_t capacity,
                                       const char* key, void* value,
                                       size_t* plength) {
    uint64_t hash = gen_hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity - 1));
    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            entries[index].value = value;
            return entries[index].key;
        }
        index++;
        if (index >= capacity) index = 0;
    }
    if (plength != NULL) {
        key = strdup(key);
        if (key == NULL) return NULL;
        (*plength)++;
    }
    entries[index].key = (char*)key;
    entries[index].value = value;
    return key;
}

static int HashTable_expand(HashTable* table) {
    size_t new_capacity = table->capacity * 2;
    HashTableEntry* new_entries = calloc(new_capacity, sizeof(HashTableEntry));
    for (size_t i = 0; i < table->capacity; i++) {
        HashTableEntry entry = table->entries[i];
        if (entry.key != NULL)
            HashTable_set_entry(new_entries, new_capacity, entry.key,
                                entry.value, NULL);
    }
    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return 1;
}

const char* HashTable_set(HashTable* table, const char* key, void* value) {
    if (table->length >= table->capacity / 2) HashTable_expand(table);
    return HashTable_set_entry(table->entries, table->capacity, key, value,
                               &table->length);
}
