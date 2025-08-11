
#include "pathfinding.h"

/**
 * dfs_graph -	recursive backtracking on graph vertices
 * @v:		current vertex
 * @target:	target vertex
 * @visited:	visited vertices
 * @q:		queue for the path
 *
 * Return:	1 if target is found, 0 otherwise
 */
int dfs_graph(vertex_t *v, vertex_t const *target, char *visited, queue_t *q)
{
	edge_t *e;									/* edge iterator */
	char *name_copy;							/* copy of vertex name */

	if (!v || visited[v->index])				/* check if vertex is valid */
		return (0);

	printf("Checking %s\n", v->content);		/* print current vertex */
	visited[v->index] = 1;						/* mark as visited */

	if (v == target)							/* if target is reached */
	{
		name_copy = strdup(v->content);			/* duplicate vertex name */
		if (!name_copy || !queue_push_front(q, name_copy))
		{
			free(name_copy);
			return (0);
		}
		return (1);								/* target found */
	}

	for (e = v->edges; e; e = e->next)			/* iterate over edges */
	{
		if (dfs_graph(e->dest, target, visited, q))	/* recursive DFS */
		{
			name_copy = strdup(v->content);
			if (!name_copy || !queue_push_front(q, name_copy))
			{
				free(name_copy);
				return (0);
			}
			return (1);
		}
	}
	return (0);									/* target not found */
}

/**
 * backtracking_graph -	find first path from start to target using backtracking
 * @graph:				graph to traverse
 * @start:				starting vertex
 * @target:				target vertex
 * Return:				queue of vertex names from start to target
 *						or NULL if not found
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
							vertex_t const *target)
{
	queue_t *q;							/* queue for the path */
	char *visited;						/* visited vertices */
	int ok;								/* DFS return value */

	if (!graph || !start || !target)
		return (NULL);

	q = queue_create();					/* create the path queue */
	if (!q)
		return (NULL);

	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
	{
		queue_delete(q);
		return (NULL);
	}

	ok = dfs_graph((vertex_t *)start, target, visited, q);	/* DFS call */
	free(visited);

	if (!ok)
	{
		queue_delete(q);
		return (NULL);
	}
	return (q);							/* return the path queue */
}
