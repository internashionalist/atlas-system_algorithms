#include "heap.h"

/**
 * heap_create -	creates a Heap data structure
 * @data_cmp:		pointer to a comparison function that compares
 *					two nodes' data
 *
 * Return:			pointer to the newly created heap_t structure
 *					or NULL on failure
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap;						/* ptr to heap structure */

	if (data_cmp == NULL)				/* NULL check */
		return (NULL);

	heap = malloc(sizeof(heap_t));		/* heap memory allocation */
	if (heap == NULL)
		return (NULL);

	heap->root = NULL;					/* init root to NULL */
	heap->size = 0;						/* init size to 0 */
	heap->data_cmp = data_cmp;			/* assign comparison function */

	return (heap);						/* return newly created heap */
}
