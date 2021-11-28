#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ht.h"

static int hash(int key, size_t capacity);
static void double_capacity(HashTable *ht);

// TODO: What's a good sentinel value for occupied buckets?
#define SENTINEL_VALUE       \
    {                        \
        .key = 0, .value = 0 \
    }

/*
NOTE: This hash table implementation assumes that 0 (NULL) is not a valid value for a key.
*/

HashTable ht_create()
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

void ht_destroy(HashTable ht)
{
    assert(ht.key_values);
    free(ht.key_values);
}

void ht_set(HashTable *ht, int key, int value)
{
    assert(ht);

    if (2 * ht->size >= ht->capacity)
    {
        double_capacity(ht);
    }

    int bucket_index = hash(key, ht->capacity);
    KeyValue sentinel = SENTINEL_VALUE;

    // Increment the index until we hit an empty bucket or we hit the index where the previous value for `key` is.
    while (!kv_is_equal(ht->key_values[bucket_index], sentinel) && (ht->key_values[bucket_index].key != key))
    {
        bucket_index = (bucket_index + 1) % ht->capacity;
    }

    KeyValue kv_to_insert = {.key = key, .value = value};
    ht->key_values[bucket_index] = kv_to_insert;
    ht->size++;
}

int ht_get(HashTable *ht, int key)
{
    assert(ht);

    int bucket_index = hash(key, ht->capacity);
    KeyValue sentinel = SENTINEL_VALUE;

    while (true)
    {
        KeyValue current_kv = ht->key_values[bucket_index];

        if (kv_is_equal(current_kv, sentinel))
        {
            return -1;
        }

        if (current_kv.key == key)
        {
            return current_kv.value;
        }

        bucket_index = (bucket_index + 1) % ht->capacity;
    }
}

bool kv_is_equal(KeyValue kv_1, KeyValue kv_2)
{
    return (kv_1.key == kv_2.key) && (kv_1.value == kv_2.value);
}

void ht_print(HashTable *ht)
{
    KeyValue sentinel = SENTINEL_VALUE;

    printf("{\n");
    printf("Size: %zu\n", ht->size);
    printf("Capacity: %zu\n", ht->capacity);
    for (int i = 0; i < ht->capacity; i++)
    {
        KeyValue current_kv = ht->key_values[i];
        if (!kv_is_equal(current_kv, sentinel))
        {
            printf("(Key: %i, Value: %i, Key_hash: %i, Actual_index: %i)\n", current_kv.key, current_kv.value, hash(current_kv.key, ht->capacity), i);
        }
    }
    printf("}\n");
}

static int hash(int key, size_t capacity)
{
    return (key * (key + 3)) % capacity;
}

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
    KeyValue sentinel = SENTINEL_VALUE;

    // Reassign the old buckets to their new positions now that the capacity is different.
    for (int i = 0; i < ht->capacity; i++)
    {
        KeyValue old_kv = ht->key_values[i];
        if (!kv_is_equal(old_kv, sentinel))
        {
            ht_set(&new_ht, old_kv.key, old_kv.value);
        }
    }

    free(ht->key_values);

    ht->size = new_ht.size;
    ht->capacity = new_ht.capacity;
    ht->key_values = new_ht.key_values;
}
