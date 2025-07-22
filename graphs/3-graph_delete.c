#include "graphs.h"

/**
 * graph_delete -	deletes an entire graph and frees memory
 * @graph:			pointer to the graph to delete
 *
 * Return:			void
 */
void graph_delete(graph_t *graph)
{
	vertex_t *curr_vertex, *next_vertex;	/* vertex iterators */
	edge_t *curr_edge, *next_edge;			/* edge iterators */

	if (!graph)
		return;

	curr_vertex = graph->vertices;			/* start at head of vertex list */
	while (curr_vertex != NULL)				/* iterate through, free verts */
	{
		next_vertex = curr_vertex->next;	/* store vert pointer first */

		curr_edge = curr_vertex->edges;		/* start at head of edge list */

		while (curr_edge != NULL)			/* iterate through, free edges */
		{
			next_edge = curr_edge->next;	/* store pointer */
			free(curr_edge);				/* free current edge */
			curr_edge = next_edge;			/* move to next edge */
		}

		free(curr_vertex->content);			/* free vertex content */
		free(curr_vertex);					/* free vertex structure */

		curr_vertex = next_vertex;			/* move to next vertex */
	}

	free(graph);							/* lastly, free graph structure */
}
