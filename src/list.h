#pragma once

#include <stdint.h>

typedef struct List
{
	uint32_t size;
	uint32_t capacity;
	int *elements;
} List;

void list_init(List *list);
void list_push(List *list, int value);
int list_get(List *list, uint32_t index);
void list_print(List *list);
void list_destroy(List *list);
