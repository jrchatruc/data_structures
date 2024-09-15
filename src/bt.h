#pragma once

typedef struct BTNode
{
	int key;
	struct BTNode *left;
	struct BTNode *right;
} BTNode;

BTNode *bt_insert(BTNode *root, int key);
BTNode *bt_find_min(BTNode *root);
BTNode *bt_find_max(BTNode *root);
BTNode *bt_find(BTNode *root, int key);
int bt_height(BTNode *root);
BTNode *bt_delete(BTNode *root, int key);
void bt_in_order_traversal(BTNode *root);
BTNode *bt_destroy(BTNode *root);
void bt_print(BTNode *root);
