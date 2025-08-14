#include "pathfinding.h"

/**
 * extract_min -	finds vertex with minimum distance
 * @dist:			array of distances
 * @used:			array of used vertices
 * @n:				number of vertices
 *
 * Return:			index of vertex with minimum distance or -1 if none found
 */
int extract_min(unsigned long *dist, char *used, size_t n)
{
	size_t i;								/* iterator */
	int idx = -1;							/* idx of vertex w min dist */
	unsigned long best = ULONG_MAX;			/* best distance */

	for (i = 0; i < n; i++)					/* iterate over vertices */
	{
		if (!used[i] && dist[i] < best)		/* if unvisited / < best dist */
		{
			best = dist[i];					/* update best dist */
			idx = (int)i;					/* update idx */
		}
	}
	return (idx);							/* return idx of min dist vertex */
}

/**
 * relax_edges -	relaxes edges from vertex ui
 * @vmap:			vertex map
 * @ui:				index of the vertex to relax edges from
 * @dist:			array of distances
 * @parent:			array of parent vertices
 * @used:			array of used vertices
 *
 * Return:			void
 */
void relax_edges(
	vertex_t **vmap, int ui, unsigned long *dist, int *parent, char *used)
{
	edge_t *e;										/* edge iterator */
	unsigned long new_dist;							/* new distance */

	for (e = vmap[ui]->edges; e; e = e->next)		/* iterate over edges */
	{
		if (used[e->dest->index] || dist[ui] == ULONG_MAX)	/* if dest used */
			continue;							/* or ui unreachable, skip */

		new_dist = dist[ui] + (unsigned long)e->weight;	/* calc new dist */
		if (new_dist < dist[e->dest->index])		/* if new dist better */
		{
			dist[e->dest->index] = new_dist;		/* update distance */
			parent[e->dest->index] = ui;			/* update parent */
		}
	}
}

/**
 * run_dijkstra -	runs Dijkstra's algorithm, core loop
 * @vmap:			vertex map
 * @n:				number of vertices
 * @start:			starting vertex
 * @target:			target vertex
 * @dist:			array of distances
 * @parent:			array of parent vertices
 * @used:			array of used vertices
 *
 * Return:			void
 */
void run_dijkstra(vertex_t **vmap, size_t n, vertex_t const *start,
				  vertex_t const *target, unsigned long *dist,
				  int *parent, char *used)
{
	int ui;											/* current vertex index */
	const char *start_name;							/* starting vertex name */

	start_name = ((vertex_t *)start)->content;		/* get name */

	while ((ui = extract_min(dist, used, n)) != -1)	/* process vertices */
	{
		if (used[ui])								/* if already used */
			continue;								/* skip */
		printf("Checking %s, distance from %s is %lu\n",
			   vmap[ui]->content, start_name,
			   dist[ui] == ULONG_MAX ? 0 : dist[ui]);	/* print info */
		used[ui] = 1;								/* mark as used */
		if ((int)target->index == ui)				/* if target found */
			break;									/* stop looking */
		relax_edges(vmap, ui, dist, parent, used);	/* relax edges */
	}
}

/**
 * build_path -		pushes duplicated names from target back to start
 * @q:				queue to push names into
 * @vmap:			vertex map
 * @parent:			array of parent vertices
 * @target:				index of target vertex
 *
 * Return:			1 on success, 0 on failure
 */
int build_path(queue_t *q, vertex_t **vmap, int *parent, int target)
{
	int cur = target;								/* current vertex */
	size_t name_len;								/* vertex name length */
	char *copy;										/* duplicate name */

	while (cur != -1)								/* traverse path */
	{
		name_len = strlen(vmap[cur]->content) + 1;	/* get name length */
		copy = malloc(name_len);					/* memory for dup name */
		if (!copy)
			return (0);
		memcpy(copy, vmap[cur]->content, name_len);	/* duplicate name */
		if (!queue_push_front(q, copy))				/* push to queue */
		{
			free(copy);
			return (0);
		}
		cur = parent[cur];							/* move to parent */
	}
	return (1);										/* success */
}

/**
 * dijkstra_graph - finds the shortest path using Dijkstra's algorithm
 * @graph:			graph to traverse
 * @start:			starting vertex
 * @target:			target vertex
 * Return:			queue of char* names from start to target or NULL
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
						vertex_t const *target)
{
	size_t n, i;								/* number verts, index */
	vertex_t **vmap, *v;						/* vertex map, iterator */
	unsigned long *dist;						/* distance array */
	int *parent;								/* parent array */
	char *used;									/* used array */
	queue_t *q;									/* result queue */

	if (!graph || !start || !target)			/* input check */
		return (NULL);
	n = graph->nb_vertices;						/* get number of vertices */
	q = queue_create();							/* create result queue */
	vmap = malloc(sizeof(*vmap) * n);			/* create vertex map */
	dist = malloc(sizeof(*dist) * n);			/* create distance array */
	parent = malloc(sizeof(*parent) * n);		/* create parent array */
	used = calloc(n, sizeof(*used));			/* create used array */
	if (!q || !vmap || !dist || !parent || !used)
	{
		if (q)
			queue_delete(q);
		free(vmap);
		free(dist);
		free(parent);
		free(used);
		return (NULL);
	}
	for (v = graph->vertices; v; v = v->next)	/* create vertex map */
		vmap[v->index] = v;
	for (i = 0; i < n; i++)						/* initialize arrays */
	{
		dist[i] = ULONG_MAX;
		parent[i] = -1;
	}
	dist[start->index] = 0;						/* start dist to 0 */
	run_dijkstra(vmap, n, start, target, dist, parent, used);	/* RUN IT */
	if (!used[target->index])					/* if target not reached */
	{
		queue_delete(q);
		q = NULL;
	}
	else if (!build_path(q, vmap, parent, target->index))	/* build path */
	{
		queue_delete(q);
		q = NULL;
	}
	free(vmap);
	free(dist);
	free(parent);
	free(used);
	return (q);									/* return result queue */
}
