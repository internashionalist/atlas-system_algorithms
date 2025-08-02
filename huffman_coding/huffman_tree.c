#include "heap/heap.h"
#include "huffman.h"

/**
 * huffman_tree -	builds the Huffman tree from data/frequency arrays
 * @data:			array of characters
 * @freq:			array of frequencies
 * @size:			number of items in arrays (same length)
 *
 * Return:			pointer to the root node of the Huffman tree
 *					or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *pq;								/* priority queue */
	binary_tree_node_t *root;				/* root of the Huffman tree */

	/* checks*/
	if (!data || !freq || size == 0)
		return (NULL);

	/* create the priority queue */
	pq = huffman_priority_queue(data, freq, size);
	if (!pq)
		return (NULL);

	/* build the Huffman tree */
	while (pq->size > 1)
	{
		/* extract two minimums and insert their parent */
		if (!huffman_extract_and_insert(pq))
			return (NULL);
	}

	/* get the root of the Huffman tree */
	root = NULL;
	if (pq->root)
		root = (binary_tree_node_t *)pq->root->data;

	/* clean up */
	heap_delete(pq, NULL);

	/* return the root of the Huffman tree */
	return (root);
}
