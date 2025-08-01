#include "heap.h"

/**
 * descend -		restores min‑heap order starting at given node using
 *					bubble‑down method
 * @node:			subtree root to descend from
 * @cmp:			comparison between two data pointers
 *
 * Return:			void
 */
void descend(binary_tree_node_t *node, int (*cmp)(void *, void *))
{
	/* bubble-down */
	while (1)
	{
		binary_tree_node_t *smallest = node;	/* assume node is smallest */
		binary_tree_node_t *l = node->left;		/* left child */
		binary_tree_node_t *r = node->right;	/* right child */

		/* compare with left and right children */
		if (l && cmp(l->data, smallest->data) < 0)
			smallest = l;
		if (r && cmp(r->data, smallest->data) < 0)
			smallest = r;

		/* if node is smallest, we're done */
		if (smallest == node)
			break;

		/* otherwise, swap node with smallest child */
		swap_pointers(node, smallest);
		node = smallest;
	}
}

/**
 * locate_last -	find the last node inserted in the heap
 * @heap:			pointer to heap
 *
 * Return:			pointer to last node or NULL on failure
 */
binary_tree_node_t *locate_last(const heap_t *heap)
{
	size_t bit_flag = 1;				/* guides traversal */
	binary_tree_node_t *node;			/* current node */

	if (!heap || !heap->root)			/* no heap or no root */
		return (NULL);

	if (heap->size == 1)				/* only root exists */
		return (heap->root);

	/* find the highest bit set in size */
	while ((bit_flag << 1) <= heap->size)
		bit_flag <<= 1;

	/* traverse the heap to find the last node */
	node = heap->root;
	for (bit_flag >>= 1; bit_flag; bit_flag >>= 1)
		node = (heap->size & bit_flag) ? node->right : node->left;

	return (node);
}

/**
 * heap_extract -	remove and return the data stored in the root of a heap
 * @heap:			pointer to the heap
 *
 * Return:			pointer to the data stored in the root node
 *					or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	void *root_data;					/* data to return */
	binary_tree_node_t *last;			/* last node in heap */

	/* checks */
	if (!heap || !heap->root || heap->size == 0)
		return (NULL);

	/* save root data to return */
	root_data = heap->root->data;

	/* if only one node exists */
	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (root_data);
	}

	/* locate last node in heap */
	last = locate_last(heap);

	/* swap root with last node */
	heap->root->data = last->data;

	/* unlink last node from its parent */
	if (last->parent->left == last)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;

	/* free last node and decrement size */
	free(last);
	heap->size--;

	/* repair heap order */
	descend(heap->root, heap->data_cmp);

	/* return data in root */
	return (root_data);
}
