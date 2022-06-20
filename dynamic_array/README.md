# Dynamic Array

A list of integers that grows dynamically as more elements are appended.

## Usage

``` C
List list;
list_init(&list);

// Append value 10
list_push(&list, 10);

// Retrieve value at index 0 (10 in this case).
int result = list_get(&list, 0);

// Clean up afterwards
list_destroy(&list);
```
