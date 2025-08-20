#include "nary_trees.h"

/*
 * subtree_depth -	computes the depth of the subtree
 * @node:			current position in the N-ary tree
 *
 * Return:			depth of the subtree
 */
size_t subtree_depth(nary_tree_t const *node)
{
	size_t best = 1;							/* at least this node */
	size_t height;									/* height of child subtree */
	nary_tree_t const *child;					/* current child */

	child = node->children;						/* iterate children list */
	while (child)
	{
		height = subtree_depth(child);				/* child subtree height */

		if (height + 1 > best)						/* path via this child */
			best = height + 1;
		child = child->next;					/* move to next sibling */
	}

	return (best);								/* return max depth */
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

	return (subtree_depth(node));
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
		return (max1 + max2 + 1);			/* return their sum + 1 */
	else if (max1)							/* if only first max found */
		return (max1 + 1);					/* return first max + 1 */

	return (1);								/* tree with only root */
}
