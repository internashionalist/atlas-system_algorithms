#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queues.h"
#include "graphs.h"

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;


/* PROTOTYPES */

/* TASK 0 */
queue_t *backtracking_array(
	char **map, int rows, int cols, point_t const *start,
	point_t const *target);
int ok(int x, int y, int rows, int cols);
int push_point(queue_t *q, int x, int y);
int dfs_dirs(
	char **map, int rows, int cols, int x, int y, int tx,
	int ty, char **vis, queue_t *q);
char **alloc_vis(int rows, int cols);
int dfs(char **map, int rows, int cols, int x, int y, int tx, int ty,
	char **vis, queue_t *q);
void free_vis(char **vis, int rows);

/* TASK 1 */
queue_t *backtracking_graph(
	graph_t *graph, vertex_t const *start, vertex_t const *target);

/* TASK 2 */
queue_t *dijkstra_graph(
	graph_t *graph, vertex_t const *start, vertex_t const *target);

#endif // PATHFINDING_H
