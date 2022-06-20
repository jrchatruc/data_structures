#include <stdlib.h>
#include <assert.h>
#include "list.h"

#define ITERATIONS 1e6

int main()
{
    List list;
    list_init(&list);

    for (int i = 0; i < ITERATIONS; i++)
    {
        list_push(&list, i);
    }

    for (int j = 0; j < ITERATIONS; j++)
    {
        int result = list_get(&list, j);
        assert(result == j);
    }

    list_destroy(&list);
    assert(list.elements == NULL);

    return 0;
}
