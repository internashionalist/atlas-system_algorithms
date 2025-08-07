#include "heap/heap.h"
#include "huffman.h"
#include <stdlib.h>

/**
 * compare_freq -	compares the frequencies of two nested nodes' symbols
 * @p1:				first pointer (to node)
 * @p2:				second pointer (to node)
 *
 * Return:			-1 if first < second, 0 if equal, 1 if first > second
 */
static int compare_freq(void *p1, void *p2)
{
	binary_tree_node_t *n1, *n2;		/* pointers to nodes */
	symbol_t *s1, *s2;					/* pointers to symbols */
	size_t f1, f2;						/* frequencies of symbols */

	n1 = (binary_tree_node_t *)p1;		/* cast pointers to nodes */
	n2 = (binary_tree_node_t *)p2;

	if (!n1 && !n2)
		return (0);
	if (!n1)
		return (-1);
	if (!n2)
		return (1);

	s1 = (symbol_t *)n1->data;			/* cast node data to symbols */
	s2 = (symbol_t *)n2->data;
	f1 = s1 ? s1->freq : 0;				/* get frequencies */
	f2 = s2 ? s2->freq : 0;

	if (f1 < f2)						/* compare frequencies */
		return (-1);
	else if (f1 > f2)
		return (1);

	if (s1 && s2)						/* tie-break by character */
	{
		int c1 = (unsigned char)s1->data;
		int c2 = (unsigned char)s2->data;
		if (c1 < c2)
			return (-1);
		else if (c1 > c2)
			return (1);
	}
	else if (!s1 && s2)					/* NULL = > */
		return (-1);
	else if (s1 && !s2)
		return (1);

	return (0);
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
		if (!heap_insert(heap, nested))			/* insert nested node */
		{
			free(nested);
			free(sym);
			heap_delete(heap, NULL);
			return (NULL);
		}
	}
	return (heap);								/* return the created heap */
}
