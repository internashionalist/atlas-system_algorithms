#include "heap.h"

/**
 * free_subtree -	frees a binary subtree recursively
 * @node:			pointer to subtree root
 * @free_data:		pointer to function that frees node data
 *
 * Return:			void
 */
static void free_subtree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)								/* NULL check */
		return;

	free_subtree(node->left, free_data);	/* free left subtree */
	free_subtree(node->right, free_data);	/* free right subtree */

	if (free_data)					/* free node data if function provided */
		free_data(node->data);
	free(node);								/* free the node itself */
}

/**
 * heap_delete -	deletes a heap and its nodes
 * @heap:			pointer to the heap to delete
 * @free_data:		pointer to function that frees node data
 *
 * Return: void
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)								/* NULL check */
		return;

	free_subtree(heap->root, free_data);	/* free nodes */
	free(heap);								/* free heap structure */
}
