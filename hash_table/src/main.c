#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "ht.h"

bool is_power_of_two(int x)
{
    return (x & (x - 1)) == 0;
}

int main()
{
    HashTable ht = ht_create();

    for (int i = 1; i < (1 << 8) + 1; i++)
    {
        ht_set(&ht, i, i);
        // Print the Hash table each time it has to be resized.
        if (is_power_of_two(i))
        {
            ht_print(&ht);
        }
    }

    for (int i = 1; i < (1 << 8) + 1; i++)
    {
        int result = 0;
        bool found = ht_get(&ht, i, &result);
        assert(found);
        found = ht_get(&ht, -i, &result);
        assert(!found);
        assert(result == i);
    }

    ht_destroy(&ht);
    assert(ht.key_values == NULL);

    return 0;
}
