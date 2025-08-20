#include "nary_trees.h"

/**
 * path_exists -	checks if a path exists in an N-ary tree
 * @root:			pointer to the root node of the tree
 * @path:			NULL-terminated array of strings representing the path
 *
 * Return:			1 if the whole path exists from root down the tree,
 *					0 otherwise
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	const nary_tree_t *curr;				/* current node in the tree */
	const nary_tree_t *child;				/* current child node */
	int i;									/* iterator for path array */

	if (!root || !path || !path[0])			/* NULL checks */
		return (0);

	if (strcmp(root->content, path[0]) != 0)	/* first element must match */
		return (0);

	curr = root;							/* start from the root */
	for (i = 1; path[i]; i++)				/* iterate through the path */
	{
		child = curr->children;				/* scan current node's children */
		while (child && strcmp(child->content, path[i]) != 0)
			child = child->next;			/* find matching child */

		if (!child)							/* if no matched child found */
			return (0);

		curr = child;						/* descend to matched child */
	}

	return (1);								/* whole path exists */
}
