#include <stdio.h>
#include <math.h>

#include "ht.h"

bool is_power_of_two(int x)
{
    return (x & (x - 1)) == 0;
}

int main(int argc, char *argv[])
{
    HashTable ht = ht_create();

    for (int i = 1; i < pow(2, 8) + 1; i++)
    {
        ht_set(&ht, i, i);
        if (is_power_of_two(i))
        {
            ht_print(&ht);
        }
    }

    return 0;
}
