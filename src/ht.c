#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ht.h"

static int hash(int key, uint32_t capacity);
static void double_capacity(HashTable *ht);

HashTable ht_create(void)
{
	HashTable ht;
	ht.size = 0;
	ht.capacity = INITIAL_CAPACITY;
	ht.key_values = calloc(ht.capacity, sizeof(KeyValue));

	if (ht.key_values == NULL)
	{
		fprintf(stderr, "Not enough memory to allocate HashTable\n");
		abort();
	}

	return ht;
}

void ht_destroy(HashTable *ht)
{
	assert(ht->key_values);
	free(ht->key_values);
	ht->key_values = NULL;
	ht->capacity = 0;
	ht->size = 0;
}

void ht_set(HashTable *ht, int key, int value)
{
	assert(ht);

	if (2 * ht->size >= ht->capacity)
	{
		double_capacity(ht);
	}

	int bucket_index = hash(key, ht->capacity);

	// Increment the index until we hit an empty bucket or we hit the index where the previous
	// value for `key` is.
	while (ht->key_values[bucket_index].occupied && (ht->key_values[bucket_index].key != key))
	{
		bucket_index = (bucket_index + 1) % ht->capacity;
	}

	KeyValue kv_to_insert = {.key = key, .value = value, .occupied = true};
	ht->key_values[bucket_index] = kv_to_insert;
	ht->size++;
}

bool ht_get(HashTable *ht, int key, int *result)
{
	assert(ht);

	int bucket_index = hash(key, ht->capacity);

	while (true)
	{
		KeyValue current_kv = ht->key_values[bucket_index];

		if (!current_kv.occupied)
		{
			return false;
		}

		if (current_kv.key == key)
		{
			*result = current_kv.value;
			return true;
		}

		bucket_index = (bucket_index + 1) % ht->capacity;
	}
}

bool kv_is_occupied(KeyValue kv) { return kv.occupied; }

void ht_print(HashTable *ht)
{
	printf("{\n");
	printf("Size: %zu\n", ht->size);
	printf("Capacity: %zu\n", ht->capacity);
	for (uint32_t i = 0; i < ht->capacity; i++)
	{
		KeyValue current_kv = ht->key_values[i];
		if (current_kv.occupied)
		{
			printf("(Key: %i, Value: %i, Key_hash: %i, Actual_index: %i)\n",
			       current_kv.key, current_kv.value, hash(current_kv.key, ht->capacity),
			       i);
		}
	}
	printf("}\n");
}

// TODO: Replace with a more interesting hash function
static int hash(int key, uint32_t capacity) { return (key * (key + 3)) % capacity; }

static void double_capacity(HashTable *ht)
{
	assert(ht);

	int new_capacity = 2 * ht->capacity;
	KeyValue *new_key_values = calloc(new_capacity, sizeof(KeyValue));

	if (new_key_values == NULL)
	{
		fprintf(stderr, "Not enough memory to grow the HashTable\n");
		abort();
	}

	HashTable new_ht = {.size = 0, .capacity = new_capacity, .key_values = new_key_values};

	// Reassign the old buckets to their new positions now that the capacity is different.
	for (uint32_t i = 0; i < ht->capacity; i++)
	{
		KeyValue old_kv = ht->key_values[i];
		if (old_kv.occupied)
		{
			ht_set(&new_ht, old_kv.key, old_kv.value);
		}
	}

	free(ht->key_values);

	ht->size = new_ht.size;
	ht->capacity = new_ht.capacity;
	ht->key_values = new_ht.key_values;
}
