
#include "graphs.h"

/**
 * graph_add_vertex -	adds a vertex to an existing graph
 * @graph:				pointer to the graph to add the vertex to
 * @str:				string to store in the new vertex
 *
 * Return:				pointer to the created vertex or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *i, *new_vertex;				/* iterator, new vertex ptrs */

	if (!graph || !str)
		return (NULL);

	/* check for existing vertex */
	for (i = graph->vertices; i; i = i->next)
		if (strcmp(i->content, str) == 0)
			return (NULL);

	/* allocate memory for new vertex */
	new_vertex = malloc(sizeof(*new_vertex));
	if (!new_vertex)
		return (NULL);

	/* duplicate string -> store in new vertex */
	new_vertex->content = strdup(str);
	if (!new_vertex->content)
	{
		free(new_vertex);
		return (NULL);
	}

	/* init vertex fields */
	new_vertex->index = graph->nb_vertices;
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	/* if graph is empty */
	if (!graph->vertices)
		graph->vertices = new_vertex;

	/* otherwise, add to the end of the adjacency linked list */
	else
	{
		i = graph->vertices;
		while (i->next)
			i = i->next;
		i->next = new_vertex;
	}

	/* increment vertex count */
	graph->nb_vertices++;

	/* ptr to new vertex */
	return (new_vertex);
}
