#include "bt.h"
#include "ht.h"
#include "list.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>

#define ITERATIONS 1e2

int main(void)
{
	// ----------------------- Binary Tree stuff -------------------------

	BTNode *root = NULL;
	root = bt_insert(root, 20);

	assert(bt_height(root) == 0);

	root = bt_insert(root, 15);
	root = bt_insert(root, 35);

	assert(bt_height(root) == 1);

	root = bt_insert(root, 5);

	assert(bt_height(root) == 2);

	root = bt_insert(root, 10);

	assert(bt_height(root) == 3);

	root = bt_insert(root, 2);
	root = bt_insert(root, 30);
	root = bt_insert(root, 25);
	root = bt_insert(root, 18);
	root = bt_insert(root, 13);

	assert(bt_height(root) == 4);

	bt_in_order_traversal(root);
	printf("\n");

	BTNode *min = bt_find_min(root);
	assert(min->key == 2);
	printf("MIN: %i\n", min->key);

	BTNode *max = bt_find_max(root);
	assert(max->key == 35);
	printf("MAX: %i\n", max->key);

	BTNode *ten_node = bt_find(root, 10);
	assert(ten_node);

	BTNode *non_existent_node = bt_find(root, 123213);
	assert(non_existent_node == NULL);

	root = bt_delete(root, 15);
	assert(bt_height(root) == 3);

	root = bt_delete(root, 2);
	root = bt_delete(root, 10);
	root = bt_delete(root, 25);
	assert(bt_height(root) == 2);

	bt_in_order_traversal(root);
	printf("\n");

	root = bt_destroy(root);
	assert(root == NULL);

	// ----------------------- Dynamic Array/List stuff -------------------------

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

	list_print(&list);

	list_destroy(&list);
	assert(list.elements == NULL);

	// ----------------------- Hash Table stuff -------------------------

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
