#include <stdlib.h>
#include "nary_trees.h"

/**
 * traverse_helper -		recursive helper with depth parameter
 * @node:					current node
 * @action:					function to execute
 * @depth:					current depth
 *
 * Return:					maximum depth from this node
 */
size_t traverse_helper(nary_tree_t const *node,
	void (*action)(nary_tree_t const *node, size_t depth), size_t depth)
{
	size_t max_depth = depth;				/* init max depth as curr depth */
	size_t child_depth;						/* init child depth */
	nary_tree_t const *child;				/* init child */

	if (!node)								/* NULL check */
		return (depth);

	action(node, depth);					/* execute action on this node */

	child = node->children;					/* get first child */
	while (child)							/* traverse children */
	{
		child_depth = traverse_helper(child, action, depth + 1); /* recurse */
		if (child_depth > max_depth)		/* if > current max depth */
			max_depth = child_depth;		/* update max depth */
		child = child->next;				/* move to next sibling */
	}

	return (max_depth);						/* return max depth found */
}

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
	if (!root || !action)					/* NULL check */
		return (0);

	return (traverse_helper(root, action, 0)); /* call helper with depth 0 */
}
