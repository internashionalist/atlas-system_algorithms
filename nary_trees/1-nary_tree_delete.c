#include <stdlib.h>
#include "nary_trees.h"

/**
 * nary_tree_delete -	deallocates an entire N-ary tree
 * @tree:				pointer to root node of tree to delete
 *
 * Return:				void
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *child, *next;				/* child and next pointers */

	if (!tree)								/* NULL check */
		return;

	child = tree->children;					/* get first child */
	while (child)							/* traverse children */
	{
		next = child->next;					/* get next sibling */
		nary_tree_delete(child);			/* delete child subtree */
		child = next;						/* move to next sibling */
	}

	free(tree->content);					/* free content */
	free(tree);								/* free root node */
}
