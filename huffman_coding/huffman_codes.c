#include "heap.h"
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print_codes - recursively print Huffman codes from a tree
 * @node: current tree node
 * @path: buffer holding the current 0/1 path as a string
 * @depth: current depth in the tree (and index in @path)
 *
 * Return: void
 */
static void print_codes(const binary_tree_node_t *node, char *path, size_t depth)
{
    symbol_t *sym;

    if (!node)
        return;

    /* leaf node: print its symbol and code */
    if (!node->left && !node->right)
    {
        sym = (symbol_t *)node->data;
        if (sym->data != (char)-1)
        {
            if (depth == 0)
            {
                /* single-node tree: conventionally print 0 */
                printf("%c: 0\n", sym->data);
            }
            else
            {
                path[depth] = '\0';
                printf("%c: %s\n", sym->data, path);
            }
        }
        return;
    }

    /* go left: append '0' */
    path[depth] = '0';
    print_codes(node->left, path, depth + 1);

    /* go right: append '1' */
    path[depth] = '1';
    print_codes(node->right, path, depth + 1);
}

/**
 * free_tree - free a Huffman tree (nodes and symbols)
 * @node: root of the tree to free
 *
 * Return: void
 */
static void free_tree(binary_tree_node_t *node)
{
    if (!node)
        return;
    free_tree(node->left);
    free_tree(node->right);
    if (node->data)
        free(node->data);
    free(node);
}

/**
 * huffman_codes - build the Huffman tree and print codes for each symbol
 * @data: array of characters
 * @freq: array of frequencies (same length as @data)
 * @size: number of items
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
    binary_tree_node_t *root;
    char path[512]; /* ample for typical inputs */

    if (!data || !freq || size == 0)
        return (0);

    root = huffman_tree(data, freq, size);
    if (!root)
        return (0);

    print_codes(root, path, 0);
    free_tree(root);
    return (1);
}
