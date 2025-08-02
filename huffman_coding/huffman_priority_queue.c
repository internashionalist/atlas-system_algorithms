#include "heap/heap.h"
#include "huffman.h"
#include <stdlib.h>

/**
 * compare_freq -	compares the frequencies of two nested nodes' symbols
 * @p1:				first pointer (to node)
 * @p2:				second pointer (to node)
 *
 * Return:			positive if first frequency is greater,
 *					negative if second frequency is greater,
 *					zero if they are equal
 */
static int compare_freq(void *p1, void *p2)
{
    binary_tree_node_t *n1;				/* first node */
    binary_tree_node_t *n2;				/* second node */
    symbol_t *s1;						/* first symbol */
    symbol_t *s2;						/* second symbol */
    int f1;								/* first frequency */
    int f2;								/* second frequency */

    n1 = (binary_tree_node_t *)p1;		/* cast first pointer to node */
    n2 = (binary_tree_node_t *)p2;		/* cast second pointer to node */
    s1 = (symbol_t *)n1->data;			/* get first symbol from node */
    s2 = (symbol_t *)n2->data;			/* get second symbol from node */

    f1 = (int)s1->freq;					/* get first frequency */
    f2 = (int)s2->freq;					/* get second frequency */

    return (f1 - f2);					/* return difference of frequencies */
}

/**
 * huffman_priority_queue - create a min-heap for Huffman coding
 * @data:					array of characters
 * @freq:					array of frequencies
 * @size:					number of items in both arrays
 *
 * Return:					pointer to the created heap or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;								/* pointer to the heap */
	size_t i;									/* loop index */

	if (!data || !freq || size == 0)			/* checks */
		return (NULL);

	heap = heap_create(compare_freq);			/* create the heap */
	if (!heap)
		return (NULL);

	for (i = 0; i < size; i++)					/* traverse arrays */
	{
		symbol_t *sym = symbol_create(data[i], freq[i]); /* create symbol */
		binary_tree_node_t *nested;				/* pointer to nested node */

		if (!sym)
		{
			heap_delete(heap, NULL);
			return (NULL);
		}
		nested = binary_tree_node(NULL, sym);	/* create nested node */
		if (!nested)
		{
			free(sym);
			heap_delete(heap, NULL);
			return (NULL);
		}
		if (!heap_insert(heap, nested))		/* insert nested node */
		{
			free(nested);
			free(sym);
			heap_delete(heap, NULL);
			return (NULL);
		}
	}
	return (heap);								/* return the created heap */
}
