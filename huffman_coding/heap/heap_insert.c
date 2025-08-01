#include "heap.h"

/**
 * swap_pointers -	exchanges the data pointers of two nodes
 * @a:				first node
 * @b:				second node
 *
 * Return:			void
 */
void swap_pointers(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp = a->data;	/* save first node's data */

	a->data = b->data;		/* swap first's data for second's */
	b->data = tmp;			/* swap second's data for first's */
}

/**
 * find_parent -		locate the parent of the newly inserted node using
 *						array indexing logic
 * @heap:				pointer to the heap
 * @index:				index of the new node in the heap
 *
 * Return:				pointer to the parent node
 */
binary_tree_node_t *find_parent(const heap_t *heap, size_t index)
{
	size_t steps[64];					/* array to store steps */
	size_t count = 0, i;				/* number of steps recorded */
	binary_tree_node_t *node;			/* traversal node */

	/* checks */
	if (!heap || !heap->root || index < 2)
		return (NULL);

	/* record path to root */
	while (index > 1)
	{
		steps[count++] = index % 2;
		index /= 2;
	}

	/* traverse recorded path to find parent (skip last step) */
	node = heap->root;
	for (i = count - 1; i > 0; i--)
		node = steps[i] ? node->right : node->left;

	/* return parent node */
	return (node);
}

/**
 * heap_insert -	inserts a value into a min binary heap
 * @heap:			pointer to heap
 * @data:			pointer to data to insert
 *
 * Return:			pointer to the newly created node or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node, *parent;
	size_t new_index;

	if (!heap || !data)
		return (NULL);

	if (!heap->root)					/* if heap is empty, create root */
	{
		new_node = binary_tree_node(NULL, data);
		if (!new_node)
			return (NULL);
		heap->root = new_node;
		heap->size = 1;
		return (new_node);
	}

	new_index = heap->size + 1;				/* calculate index of new node */
	parent = find_parent(heap, new_index);	/* find parent */
	if (!parent)
		return (NULL);

	new_node = binary_tree_node(parent, data);	/* link new node to parent */
	if (!new_node)
		return (NULL);

	if (new_index & 1)						/* odd index => right child */
		parent->right = new_node;
	else									/* even index => left child */
		parent->left = new_node;

	heap->size++;							/* update heap size */

	while (new_node->parent &&				/* bubble up if necessary */
		   heap->data_cmp(new_node->data, new_node->parent->data) < 0)
	{
		swap_pointers(new_node, new_node->parent);
		new_node = new_node->parent;
	}

	return (new_node);
}
