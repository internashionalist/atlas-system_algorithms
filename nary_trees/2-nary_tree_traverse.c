#include <stdlib.h>
#include "nary_trees.h"

/**
 * nary_tree_traverse -		traverses an N-ary tree
 * @root:					pointer to root node of tree to traverse
 * @action:					pointer to function to execute for each node
 *
 * Return:					the biggest depth of the tree or 0 if root is NULL
 */
size_t nary_tree_traverse(nary_tree_t const *root,
	void (*action)(nary_tree_t const *node, size_t depth))
{
	size_t max_depth = 0;					/* init max depth */
	size_t child_depth;						/* init child depth */
	nary_tree_t const *child;				/* init child */

	if (!root || !action)					/* NULL check */
		return (0);

	action(root, 0);						/* execute action on root */

	child = root->children;					/* get first child */
	while (child)							/* traverse children */
	{
		child_depth = nary_tree_traverse(child, action); /* get child depth */
		if (child_depth > max_depth)		/* if > current max depth */
			max_depth = child_depth;		/* update max depth */
		child = child->next;				/* move to next sibling */
	}

	return (max_depth + 1);					/* return max depth (+1 root) */
}
