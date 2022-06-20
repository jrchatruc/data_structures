# Binary Tree

Simple binary tree with integer keys.

## Usage

``` C
BTNode *root = NULL;
root = bt_insert(root, 20);
root = bt_insert(root, 15);
root = bt_insert(root, 35);

// Node with the lowest key
BTNode *min = bt_find_min(root);

// Node with the greatest key
BTNode *max = bt_find_max(root);

// Node with key == 20
BTNode *ten_node = bt_find(root, 20);

// Delete keys
root = bt_delete(root, 15);

// Print keys in increasing order
// In this case prints `15 20 35`
bt_in_order_traversal(root);

// Clean up afterwards
bt_destroy(root);
```
