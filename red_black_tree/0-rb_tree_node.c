#include "rb_trees.h"

/**
 * rb_tree_node - creates new Red‑Black Tree node
 * @parent:			pointer to parent of new node
 * @value:			value to store in new node
 * @color:			color of the new node
 *
 * Return:			pointer to the new node or NULL on failure
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new;						/* pointer to new node */

	new = malloc(sizeof(rb_tree_t));	/* allocate its memory */
	if (new == NULL)					/* failure check */
		return (NULL);

	new->n = value;						/* set node value */
	new->color = color;					/* set node color */
	new->parent = parent;				/* set parent pointer */
	new->left = NULL;					/* set left child pointer */
	new->right = NULL;					/* set right child pointer */

	return (new);						/* return pointer to new node */
}
