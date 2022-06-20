#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

#define INITIAL_CAPACITY 16
#define ELEMENT_SIZE sizeof(int)

static void double_capacity(List *list)
{
    int *new_buffer = malloc(ELEMENT_SIZE * list->capacity * 2);

    if (new_buffer == NULL)
    {
        fprintf(stderr, "Couldn't allocate memory to grow the list");
        exit(1);
    }

    memcpy(new_buffer, list->elements, ELEMENT_SIZE * list->capacity);
    list->capacity = list->capacity * 2;
    free(list->elements);
    list->elements = new_buffer;
}

void list_init(List *list)
{
    int *initial_buffer = malloc(ELEMENT_SIZE * INITIAL_CAPACITY);

    if (initial_buffer == NULL)
    {
        fprintf(stderr, "Couldn't allocate memory for the list");
        exit(1);
    }

    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->elements = initial_buffer;
}

void list_push(List *list, int value)
{
    if (list->size == list->capacity)
    {
        double_capacity(list);
    }

    list->elements[list->size++] = value;
}

int list_get(List *list, uint32_t index)
{
    if (index >= list->size)
    {
        fprintf(stderr, "Index out of bounds");
        exit(1);
    }

    return list->elements[index];
}

void list_destroy(List *list)
{
    free(list->elements);
    list->elements = NULL;
    list->size = 0;
    list->capacity = 0;
}

void list_print(List *list)
{
    printf("[\n");

    for (uint32_t i = 0; i < list->size; i++)
    {
        printf("%i,", list->elements[i]);
    }

    printf("]\n");
}
