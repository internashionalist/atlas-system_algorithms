#include "heap/heap.h"
#include "huffman.h"

/**
 * huffman_extract_and_insert -	extracts two mins and inserts their parent
 * @priority_queue:				pointer to the priority queue
 *
 * Return:						1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *left;				/* left child */
	binary_tree_node_t *right;				/* right child */
	binary_tree_node_t *parent;				/* parent */
	symbol_t *sl, *sr, *sp;					/* respective symbols */

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	left = (binary_tree_node_t *)heap_extract(priority_queue);
	if (!left)								/* extract left child */
		return (0);

	right = (binary_tree_node_t *)heap_extract(priority_queue);
	if (!right)								/* extract right child */
		return (0);

	sl = (symbol_t *)left->data;			/* left symbol */
	sr = (symbol_t *)right->data;			/* right symbol */
	sp = symbol_create(-1, sl->freq + sr->freq);	/* parent symbol */
	if (!sp)
		return (0);

	parent = binary_tree_node(NULL, sp);	/* create parent node */
	if (!parent)
	{
		free(sp);
		return (0);
	}

	parent->left = left;					/* set left child */
	parent->right = right;					/* set right child */
	left->parent = parent;					/* set parent of left child */
	right->parent = parent;					/* set parent of right child */

	if (!heap_insert(priority_queue, parent))	/* insert into queue */
	{
		free(parent);
		free(sp);
		return (0);
	}
	return (1);								/* success */
}
