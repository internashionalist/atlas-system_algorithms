#include <stdlib.h>
#include "graphs.h"

/**
 * graph_create -	allocates memory for a new graph_t structure
 *					and initializes its members
 *
 * Return:			pointer to the newly allocated graph_t structure,
 *					or NULL on failure
 */
graph_t *graph_create(void)
{
	graph_t *graph;						/* graph struct */

	graph = malloc(sizeof(*graph));		/* memory for graph */
	if (!graph)
		return (NULL);

	graph->nb_vertices = 0;				/* init number of vertices */
	graph->vertices = NULL;				/* set vertices pointer to NULL */

	return (graph);						/* return pointer to graph */
}
