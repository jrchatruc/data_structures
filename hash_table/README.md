# Hash Table

A very simple hash table with integers as both keys and values, using linear probing to resolve collisions and

```
key --> key * (key + 3) % capacity
```

as the hash function.

## Usage

``` C
HashTable ht = ht_create();
ht_set(&ht, 10, 20);

// Get key. If there's a hit, `found` will be true and the result
// will be set in the pointer passed as the last argument.
// In this case, `found` will be true and `result` == 20.
int result = 0;
bool found = ht_get(&ht, 10, &result);

// Here, `found` is false and `result` is not modified.
bool found = ht_get(&ht, 100, &result);

// Clean up afterwards
ht_destroy(&ht)
```
