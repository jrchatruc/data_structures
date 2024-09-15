#pragma once

#include <stdbool.h>
#include <stddef.h>

#define INITIAL_CAPACITY 16;

typedef struct
{
	int key;
	int value;
	bool occupied;
} KeyValue;

typedef struct
{
	size_t size;
	size_t capacity;
	KeyValue *key_values;
} HashTable;

HashTable ht_create(void);
void ht_destroy(HashTable *ht);
void ht_set(HashTable *ht, int key, int value);
bool ht_get(HashTable *ht, int key, int *result);
void ht_delete(HashTable *ht, int key);
void ht_print(HashTable *ht);
bool kv_is_equal(KeyValue kv_1, KeyValue kv_2);
