#include "graphs.h"

/**
 * recurse_depth_first -	traverses graph using DFS recursively
 * @curr_vert:				current vertex
 * @curr_depth:				current depth
 * @callback:				user callback
 * @max_depth:				pointer to the current maximum depth found
 * @visited_array:			array marking which vertices have been visited
 *
 * Return:					void
 */
void recurse_depth_first(const vertex_t *curr_vert, size_t curr_depth,
						 void (*callback)(const vertex_t *, size_t),
						 size_t *max_depth, char *visited_array)
{
	edge_t *e;									/* edge iterator */

	/* if anything NULL or already visited, return */
	if (!curr_vert || !callback || visited_array[curr_vert->index])
		return;

	visited_array[curr_vert->index] = 1;		/* mark as visited */
	callback(curr_vert, curr_depth);			/* apply user callback */

	if (curr_depth > *max_depth)				/* if deeper than max */
		*max_depth = curr_depth;				/* update max depth found */


	e = curr_vert->edges;						/* iterate through edges */
	while (e != NULL)
	{
		recurse_depth_first(e->dest, curr_depth + 1,
							callback, max_depth, visited_array);
		e = e->next;
	}
}

/**
 * depth_first_traverse -	walks graph using DFS starting at first vertex
 * @graph:					graph to traverse
 * @action:					user callback applied to each vertex
 *
 * Return:					deepest vertex depth found or 0 on error
 */
size_t depth_first_traverse(const graph_t *graph,
							void (*action)(const vertex_t *v, size_t depth))
{
	size_t max_depth = 0;						/* max depth encountered */
	char *visited = NULL;						/* visited flags */
	vertex_t *start = NULL;						/* first vertex */

	/* NULL checks, vertices must exist */
	if (!graph || !action || graph->nb_vertices == 0)
		return (0);

	/* allocate visited flags (one byte per vertex) */
	visited = malloc(graph->nb_vertices);
	if (!visited)
		return (0);

	/* init visited array */
	memset(visited, 0, graph->nb_vertices);		/* init to 0 */
	start = graph->vertices;					/* get first vertex */
	if (!start)
	{
		free(visited);
		return (0);
	}

	/* start DFS traversal */
	recurse_depth_first(start, 0, action, &max_depth, visited);
	free(visited);

	return (max_depth);							
}
