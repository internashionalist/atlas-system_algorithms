#ifndef RB_TREES_H
#define RB_TREES_H

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

/**
 * enum rb_color_e - possible color of a Red-Black tree
 * @RED:			0 -> Red node
 * @BLACK:			1 -> Black node
 * @DOUBLE_BLACK:	2 -> Double Black node (used during deletion)
 */
typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;

/**
 * struct rb_tree_s - Red-Black tree node structure
 * @n:				integer stored in the node
 * @parent:			pointer to the parent node
 * @left:			pointer to the left child node
 * @right:			pointer to the right child node
 * @color:			color of the node (RED or BLACK)
 */
typedef struct rb_tree_s
{
	int n;
	rb_color_t color;
	struct rb_tree_s *parent;
	struct rb_tree_s *left;
	struct rb_tree_s *right;
} rb_tree_t;

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);

int rb_tree_is_valid(const rb_tree_t *tree);
int is_valid_rbt(const rb_tree_t *node, int min, int max, int *black_height);

rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
void rotate_left(rb_tree_t **root, rb_tree_t *x);
void rotate_right(rb_tree_t **root, rb_tree_t *y);
rb_tree_t *bst_insert(rb_tree_t **root, int value);
void rebalance_left(rb_tree_t **root, rb_tree_t **z);
void rebalance_right(rb_tree_t **root, rb_tree_t **z);
void rebalance(rb_tree_t **root, rb_tree_t *z);

rb_tree_t *array_to_rb_tree(int *array, size_t size);

rb_tree_t *rb_tree_remove(rb_tree_t *root, int n);

#endif /* RB_TREES_H */
