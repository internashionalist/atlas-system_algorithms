#include "graphs.h"

/**
 * bfs_loop -			helper that runs the BFS while-loop
 * @queue:				queue for BFS
 * @depth:				depth of vertex in queue
 * @visited:			visited flags
 * @front:				pointer to front index
 * @back:				pointer to back index
 * @max_depth:			pointer to max depth found
 * @action:				user callback
 *
 * Return:				void
 */
void bfs_loop(vertex_t **queue, size_t *depth, char *visited,
					 size_t *front, size_t *back, size_t *max_depth,
					 void (*action)(const vertex_t *, size_t))
{
	edge_t *e;							/* edge iterator */
	vertex_t *v;						/* current vertex */
	size_t d;							/* current vertex depth */

	while (*front < *back)				/* while vertices in queue */
	{
		v = queue[*front];				/* set current vertex */
		d = depth[*front];				/* set current vertex depth */
		(*front)++;						/* increment front index */

		action(v, d);					/* call action on current vertex */
		if (d > *max_depth)				/* update max depth if needed */
			*max_depth = d;

		e = v->edges;					/* iterate edges of current vertex */
		while (e != NULL)
		{
			if (!visited[e->dest->index])		/* if dest not visited */
			{
				visited[e->dest->index] = 1;	/* mark as visited */
				queue[*back] = e->dest;			/* add to queue */
				depth[*back] = d + 1;			/* increment depth */
				(*back)++;						/* increment back index */
			}
			e = e->next;						/* move to next edge */
		}
	}
}

/**
 * breadth_first_traverse -		goes through a graph using BFS
 * @graph:						pointer to the graph
 * @action:						function to call on each visited vertex
 *
 * Return:						deepest vertex depth reached, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
							  void (*action)(const vertex_t *v, size_t depth))
{
	vertex_t *start;							/* first vertex */
	vertex_t **queue = NULL;					/* queue for BFS */
	size_t *depth = NULL;						/* depth of vertex in queue */
	char *visited = NULL;						/* visited flags */
	size_t front = 0, back = 0, max_depth = 0;	/* indices and max depth */

	/* NULL, empty checks */
	if (!action || !graph || graph->nb_vertices == 0)
		return (0);

	start = graph->vertices;					/* get first vertex */

	/* allocate memory for BFS structures */
	queue = malloc(sizeof(*queue) * graph->nb_vertices);
	depth = malloc(sizeof(*depth) * graph->nb_vertices);
	visited = calloc(graph->nb_vertices, 1);

	if (!queue || !depth || !visited)			/* check for failure */
	{
		free(queue);
		free(depth);
		free(visited);
		return (0);
	}

	queue[back] = start;						/* first vertex */
	depth[back] = 0;							/* first vert depth is 0 */
	visited[start->index] = 1;					/* mark as visited */
	back++;										/* increment back index */

	/* BFS loop */
	bfs_loop(queue, depth, visited, &front, &back, &max_depth, action);

	free(queue);
	free(depth);
	free(visited);

	return (max_depth);							/* return max depth reached */
}
