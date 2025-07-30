#include "heap.h"

/**
 * binary_tree_node -	creates a generic binary tree node
 * @parent:				pointer to parent node
 * @data:				pointer to data to be stored in the node
 *
 * Return:				pointer to the created node or NULL on failure
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *node;					/* ptr to binary tree node */

	node = malloc(sizeof(binary_tree_node_t));	/* memory for node */
	if (node == NULL)
		return (NULL);

	node->parent = parent;						/* assign parent */
	node->left = NULL;							/* assign left child */
	node->right = NULL;							/* assign right child */
	node->data = data;							/* assign data */

	return (node);								/* return created node */
}
