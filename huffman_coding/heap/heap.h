#ifndef _HEAP_H_
#define _HEAP_H_

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * struct binary_tree_node_s - Binary tree node data structure
 *
 * @data: Data stored in a node
 * @left: Pointer to the left child
 * @right: Pointer to the right child
 * @parent: Pointer to the parent node
 */
typedef struct binary_tree_node_s
{
	void *data;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
} binary_tree_node_t;

/**
 * struct heap_s - Heap data structure
 *
 * @size: Size of the heap (number of nodes)
 * @data_cmp: Function to compare two nodes data
 * @root: Pointer to the root node of the heap
 */
typedef struct heap_s
{
	size_t size;
	int (*data_cmp)(void *, void *);
	binary_tree_node_t *root;
} heap_t;

/* PROTOTYPES */

/* Task 0 */
heap_t *heap_create(int (*data_cmp)(void *, void *));

/* Task 1 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);

/* Task 2 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data);
binary_tree_node_t *find_parent(const heap_t *heap, size_t index);
void swap_pointers(binary_tree_node_t *a, binary_tree_node_t *b);

/* Task 3 */
void *heap_extract(heap_t *heap);
void descend(binary_tree_node_t *node, int (*cmp)(void *, void *));
binary_tree_node_t *locate_last(const heap_t *heap);

/* Task 4 */
void heap_delete(heap_t *heap, void (*free_data)(void *));
void free_subtree(binary_tree_node_t *node, void (*free_data)(void *));

/* Task 5 */


#endif /* _HEAP_H_ */
