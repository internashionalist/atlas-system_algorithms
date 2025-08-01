#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "heap/heap.h"

/**
 * struct symbol_s - 	stores a char and its associated frequency
 *
 * @data:				the character
 * @freq:				the associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

/* PROTOTYPES */
symbol_t *symbol_create(char data, size_t freq);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
int huffman_extract_and_insert(heap_t *priority_queue);
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);
int huffman_codes(char *data, size_t *freq, size_t size);

#endif /* _HUFFMAN_H_ */