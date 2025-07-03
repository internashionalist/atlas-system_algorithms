#ifndef RB_TREES_H
#define RB_TREES_H

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

/**
 * enum rb_color_e - possible color of a Red-Black tree
 * @RED:		0 -> Red node
 * @BLACK:		1 -> Black node
 */
typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;

/**
 * struct rb_tree_s - Red-Black tree node structure
 * @n:			integer stored in the node
 * @parent:		pointer to the parent node
 * @left:		pointer to the left child node
 * @right:		pointer to the right child node
 * @color:		color of the node (RED or BLACK)
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

#endif /* RB_TREES_H */