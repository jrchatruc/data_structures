#pragma once

typedef struct BTNode
{
    int value;
    struct BTNode *left;
    struct BTNode *right;
} BTNode;

BTNode *bt_insert(BTNode *root, int value);
BTNode *bt_find_min(BTNode *root);
BTNode *bt_find_max(BTNode *root);
BTNode *bt_find(BTNode *root, int value);
int bt_height(BTNode *root);
BTNode *bt_delete(BTNode *root, int value);
void bt_in_order_traversal(BTNode *root);
BTNode *bt_destroy(BTNode *root);
void bt_print(BTNode *root);
