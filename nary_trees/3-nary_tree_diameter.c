#include "nary_trees.h"

/*
 * subtree_depth -	computes the depth of the subtree
 * @node:			current position in the N-ary tree
 *
 * Return:			depth of the subtree
 */
size_t subtree_depth(nary_tree_t const *node)
{
	size_t child_d, next_d = 0, max_d;			/* child, next, max depths */

	if (node == NULL)							/* NULL check */
		return (0);

	child_d = subtree_depth(node->children);	/* depth via first child */
	if (node->children)							/* if child exists */
		child_d += 1;							/* include this node */

	next_d = subtree_depth(node->next);			/* depth via next sibling */

	max_d = child_d;							/* max depth so far */
	if (next_d > max_d)							/* if next depth is greater */
		max_d = next_d;							/* update max */

	return (max_d);								/* return max depth */
}

/*
 * subtree_height -		wrapper that computes the height of the subtree
 * @node:				current position in the N-ary tree
 *
 * Return:				height of subtree
 */
size_t subtree_height(nary_tree_t const *node)
{
	if (node == NULL)
		return (0);

	return (subtree_depth(node->children) + 1);	/* height = depth + 1 */
}

/**
 * nary_tree_diameter -		computes the diameter of an N-ary tree
 * @root:					root of the N-ary tree
 *
 * Return:					diameter in nodes (0 if root is NULL)
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	nary_tree_t const *i;					/* iterator */
	size_t max1 = 0, max2 = 0, height;		/* max depths and curr height */

	if (root == NULL)
		return (0);

	i = root->children;						/* start with first child */
	while (i)								/* traverse children */
	{
		height = subtree_height(i);			/* get current child height */
		if (height > max1)					/* if new max found */
		{
			max2 = max1;					/* update second max */
			max1 = height;					/* update first max */
		}
		else if (height > max2)				/* if new second max found */
		{
			max2 = height;					/* only update second max */
		}
		i = i->next;						/* move to next sibling */
	}

	if (max1 && max2)						/* if both max's found */
		return (max1 + max2 + 2);			/* return their sum + 2 */
	else if (max1)							/* if only first max found */
		return (max1 + 1);					/* return first max + 1 */

	return (1);								/* tree with only root */
}
