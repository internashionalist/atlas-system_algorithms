#include "rb_trees.h"

/**
 * array_to_rb_tree - converts an array to a Red-Black tree
 * @array:		pointer to the first element of the array to convert
 * @size:		number of elements in @array
 *
 * Return:		pointer to root of created tree or NULL on failure
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	rb_tree_t *root = NULL;				/* initialize root of RB tree */
	size_t i;							/* loop index */

	if (!array || size == 0)			/* empty array, NULL check */
		return (NULL);

	for (i = 0; i < size; i++)			/* iterate through the array */
		rb_tree_insert(&root, array[i]); /* insert elements into RB tree */

	return (root);						/* return root of new RB tree */
}
