#include "rb_trees.h"

/**
 * is_valid_rbt - checks whether a subtree is a valid Red‑Black tree
 * @node:			pointer to the current node
 * @min:			smallest allowed value
 * @max:			largest allowed value
 * @black_height:	pointer to store the black-height of the subtree
 *
 * Return:			1 if subtree is valid Red-Black tree, otherwise 0
 */
int is_valid_rbt(const rb_tree_t *node, int min, int max, int *black_height)
{
	int left_bh, right_bh;				/* left and right black-height */

	if (node == NULL)					/* empty subtree is valid */
	{
		*black_height = 1;				/* empty black-height is 1 */
		return (1);
	}

	if (node->n < min || node->n > max)	/* value range check */
		return (0);

	if (node->color != RED && node->color != BLACK) /* color check */
		return (0);

	/* if red, cannot have red children or parent */
	if (node->color == RED)
	{
		if ((node->parent && node->parent->color == RED) ||
			(node->left  && node->left->color  == RED) ||
			(node->right && node->right->color == RED))
			return (0);
	}

	/* check children for value range */
	if (!is_valid_rbt(node->left, min, node->n - 1, &left_bh))
		return (0);
	if (!is_valid_rbt(node->right, node->n + 1, max, &right_bh))
		return (0);

	/* subtrees must have same black-height */
	if (left_bh != right_bh)
		return (0);

	/* find black-height of current node */
	*black_height = left_bh + (node->color == BLACK);

	/* if all checks passed, return 1 */
	return (1);
}

/**
 * rb_tree_is_valid - checks whether a binary tree is a valid Red‑Black tree
 * @tree: 		pointer to the root node of the tree to check
 *
 * Return:		1 if subtree is a valid Red‑Black tree, otherwise 0
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int black_height;

	/* empty tree is valid */
	if (tree == NULL)
		return (1);

	/* root must be black */
	if (tree->color != BLACK)
		return (0);

	/* return validation result */
	return (is_valid_rbt(tree, INT_MIN, INT_MAX, &black_height));
}
