#include "rb_trees.h"

/**
 * rb_tree_insert - inserts a value into a Red-Black tree
 * @tree:			pointer to root node of inserted tree
 * @value:			value to insert into tree
 *
 * Return: pointer to the newly inserted node, or NULL on failure/duplicate
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new, *parent;			/* ptrs to new node and its parent */
	rb_color_t color;					/* color of new node */
	int black_height;					/* black-height of the tree */

	if (tree == NULL)					/* NULL check */
		return (NULL);

	if (*tree == NULL)					/* if empty tree, create new root */
	{
		new = malloc(sizeof(rb_tree_t));	/* allocate for new node */
		if (new == NULL)
			return (NULL);

		new->n = value;					/* set value */
		new->color = BLACK;				/* new root is always black */
		new->parent = NULL;				/* no parent */
		new->left = NULL;				/* no left child */
		new->right = NULL;				/* no right child */
		*tree = new;					/* set new node as root */

		return (new);					/* return new node */
	}

	parent = *tree;						/* tree exists, find parent */
	while (parent != NULL)
	{
		
	}