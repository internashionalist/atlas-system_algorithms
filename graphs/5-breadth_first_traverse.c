#include "graphs.h"

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
	edge_t *e;									/* edge iterator */

	start = graph->vertices;					/* get first vertex */
	queue = malloc(sizeof(*queue) * graph->nb_vertices);
	depth = malloc(sizeof(*depth) * graph->nb_vertices);
	visited = calloc(graph->nb_vertices, 1);

	queue[back] = start;						/* first vertex */
	depth[back] = 0;							/* first vert depth is 0 */
	visited[start->index] = 1;					/* mark as visited */
	back++;										/* increment back index */

	while (front < back)						/* while vertices in queue */
	{
		vertex_t *v = queue[front];				/* current vertex */
		size_t d = depth[front];				/* current vertex depth */

		front++;								/* increment front index */
		action(v, d);					/* call action on current vertex */
		if (d > max_depth)					/* update max depth if needed */
			max_depth = d;
		e = v->edges;			/* iterate through edges of current vertex */
		while (e != NULL)
		{
			if (!visited[e->dest->index])		/* if dest not visited */
			{
				visited[e->dest->index] = 1;	/* mark as visited */
				queue[back] = e->dest;			/* add to queue */
				depth[back] = d + 1;			/* increment depth */
				back++;							/* increment back index */
			}
			e = e->next;						/* move to next edge */
		}
	}
	free(queue);
	free(depth);
	free(visited);
	return (max_depth);
}
