#include "bt.h"
#include <stdlib.h>
#include <stdio.h>

BTNode *bt_insert(BTNode *root, int value)
{
    if (root == NULL)
    {
        root = malloc(sizeof(BTNode));
        root->value = value;
        root->left = NULL;
        root->right = NULL;
    }
    else if (value < root->value)
    {
        root->left = bt_insert(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = bt_insert(root->right, value);
    }

    return root;
}

BTNode *bt_find_min(BTNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->left == NULL)
    {
        return root;
    }
    else
    {
        return bt_find_min(root->left);
    }
}

BTNode *bt_find_max(BTNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->right == NULL)
    {
        return root;
    }
    else
    {
        return bt_find_max(root->right);
    }
}

BTNode *bt_find(BTNode *root, int value)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (value < root->value)
    {
        return bt_find(root->left, value);
    }
    else if (value > root->value)
    {
        return bt_find(root->right, value);
    }
    else
    {
        return root;
    }
}

int bt_height(BTNode *root)
{
    int left_height, right_height;
    if (root == NULL)
    {
        return -1;
    }

    left_height = bt_height(root->left);
    right_height = bt_height(root->right);

    if (left_height < right_height)
    {
        return right_height + 1;
    }
    else
    {
        return left_height + 1;
    }
}

BTNode *bt_delete(BTNode *root, int value)
{
    BTNode *temp = NULL;

    if (root == NULL)
    {
        return NULL;
    }
    else if (value < root->value)
    {
        root->left = bt_delete(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = bt_delete(root->right, value);
    }
    else if (root->left && root->right)
    {
        temp = bt_find_max(root->left);
        root->value = temp->value;
        root->left = bt_delete(root->left, root->value);
    }
    else
    {
        temp = root;

        if (root->left == NULL)
        {
            root = root->right;
        }
        else if (root->right == NULL)
        {
            root = root->left;
        }

        free(temp);
    }

    return root;
}

// This means that we output values in increasing order.
void bt_in_order_traversal(BTNode *root)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left)
    {
        bt_in_order_traversal(root->left);
    }

    printf("%i ", root->value);

    if (root->right)
    {
        bt_in_order_traversal(root->right);
    }

    return;
}

BTNode *bt_destroy(BTNode *root)
{
    if (root != NULL)
    {
        bt_destroy(root->left);
        bt_destroy(root->right);
        free(root);
    }

    return NULL;
}

// TODO: Make this draw an ASCII representation
void bt_print(BTNode *root)
{
    if (root->left)
    {
        bt_print(root->left);
    }

    int left_value = root->left ? root->left->value : 0;
    int right_value = root->right ? root->right->value : 0;

    printf("NODE: KEY=%i CHILDREN: (%i, %i)\n", root->value, left_value, right_value);

    if (root->right)
    {
        bt_print(root->right);
    }
}
