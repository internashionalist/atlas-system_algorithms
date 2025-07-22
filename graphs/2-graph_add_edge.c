#include "graphs.h"

/**
 * append_edge -	appends an edge node to the end of a vertex edge list
 * @vert_list:		pointer to vertex with list being appended to
 * @edge_node:		pointer to the edge node to append
 *
 * Return:			void
 */
void append_edge(vertex_t *vert_list, edge_t *edge_node)
{
	edge_t *tmp;							/* iterator */

	if (!vert_list->edges)					/* edge list empty */
		vert_list->edges = edge_node;		/* set new edge as head */
	else
	{
		tmp = vert_list->edges;				/* find last edge in list */
		while (tmp->next)					/* iterate until last edge */
			tmp = tmp->next;
		tmp->next = edge_node;				/* append new edge */
	}
	vert_list->nb_edges++;					/* increment edge count */
}

/**
 * create_edge -	allocates & initializes a single edge to dest_vert
 * @dest_vert:		destination vertex
 *
 * Return:			pointer to new edge or NULL on failure
 */
edge_t *create_edge(vertex_t *dest_vert)
{
	edge_t *e = malloc(sizeof(*e));			/* allocate memory for new edge */

	if (!e)
		return (NULL);
	e->dest = dest_vert;					/* set destination vertex */
	e->next = NULL;							/* init next pointer to NULL */

	return (e);								/* return pointer to new edge */
}


/**
 * graph_add_edge -	adds an edge between two existing vertices
 * @graph:			pointer to the graph
 * @src:			name of source vertex
 * @dest:			name of destination vertex
 * @type:			UNIDIRECTIONAL or BIDIRECTIONAL
 *
 * Return:			1 on success, 0 on failure
 */
int graph_add_edge(
	graph_t *graph, const char *src, const char *dest, edge_type_t type)
{
	vertex_t *v_src = NULL, *v_dest = NULL;	/* source & destination verts */
	edge_t *e_src = NULL, *e_dest = NULL;	/* source & destination edges */

	if (!graph || !src || !dest)			/* check for NULL pointers */
		return (0);

	for (v_src = graph->vertices;			/* find source vertex */
	     v_src && strcmp(v_src->content, src); v_src = v_src->next)
		;
	for (v_dest = graph->vertices;			/* find destination vertex */
	     v_dest && strcmp(v_dest->content, dest); v_dest = v_dest->next)
		;
	if (!v_src || !v_dest)					/* if either vertex not found */
		return (0);

	e_src = create_edge(v_dest);			/* create edge to destination */
	if (!e_src)
		return (0);

	if (type == BIDIRECTIONAL)				/* if bi, create reverse edge */
	{
		e_dest = create_edge(v_src);		/* create edge to source */
		if (!e_dest)
		{
			free(e_src);
			return (0);
		}
	}

	append_edge(v_src, e_src);				/* append edge to source vertex */
	if (type == BIDIRECTIONAL)				/* if bi, append reverse edge */
		append_edge(v_dest, e_dest);

	return (1);								/* SUCCESS */
}
