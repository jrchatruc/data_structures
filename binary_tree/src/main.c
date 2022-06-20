#include <stdio.h>
#include <assert.h>
#include "bt.h"

int main()
{
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
    assert(min->value == 2);
    printf("MIN: %i\n", min->value);

    BTNode *max = bt_find_max(root);
    assert(max->value == 35);
    printf("MAX: %i\n", max->value);

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

    return 0;
}
