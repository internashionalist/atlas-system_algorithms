#include <stdlib.h>
#include <string.h>
#include "nary_trees.h"

/**
 * nary_tree_insert -	inserts a node in an N-ary tree
 * @parent:				pointer to parent node or NULL to create a root
 * @str:				string to duplicate and store in created node
 *
 * Return:				pointer to created node or NULL on failure
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *node;						/* new node */
	char *str_dup;							/* duplicated string */

	if (!str)
		return (NULL);

	node = malloc(sizeof(*node));			/* memory for new node */
	if (!node)
		return (NULL);

	str_dup = strdup(str);					/* duplicate string */
	if (!str_dup)
	{
		free(node);
		return (NULL);
	}

	node->content = str_dup;				/* set content */
	node->parent = parent;					/* set parent */
	node->nb_children = 0;					/* init number of children */
	node->children = NULL;					/* init children */
	node->next = NULL;						/* init next */

	if (parent)								/* if parent is not NULL */
	{
		node->next = parent->children;		/* link node to children */
		parent->children = node;			/* set node as first child */
		parent->nb_children++;				/* increment number of children */
	}

	return (node);							/* return new node */
}
