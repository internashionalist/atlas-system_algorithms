#include "pathfinding.h"

/**
 * ok -		checks if coordinates are within bounds
 * @x:		X coordinate
 * @y:		Y coordinate
 * @rows:	Number of rows in the map
 * @cols:	Number of columns in the map
 *
 * Return:	1 if inside bounds, else 0
 */
int ok(int x, int y, int rows, int cols)
{
	return (x >= 0 && x < cols && y >= 0 && y < rows);
}

/**
 * dfs -		recursive DFS function to find the target
 * @map:		the map
 * @rows:		number of rows in the map
 * @cols:		number of columns in the map
 * @x:			current x coordinate
 * @y:			current y coordinate
 * @tx:			target x coordinate
 * @ty:			target y coordinate
 * @vis:		visited cells
 * @q:			queue for the path
 *
 * Return:		1 if target is found, 0 otherwise
 */
int dfs(char **map, int rows, int cols, int x, int y, int tx, int ty,
		char **vis, queue_t *q)
{
	point_t *pt;							/* current point */

	if (!ok(x, y, rows, cols))				/* check bounds */
        return (0);

    if (map[y][x] != '0' || vis[y][x])		/* check if cell is valid */
        return (0);

    printf("Checking coordinates [%d, %d]\n", x, y);
    vis[y][x] = 1;							/* mark as visited */

	if (x == tx && y == ty)					/* check if target is reached */
	{
		pt = malloc(sizeof(*pt));
		if (!pt)
			return (0);
		pt->x = x;							/* set x coordinate */
		pt->y = y;							/* set y coordinate */
		if (!queue_push_front(q, pt))		/* push point to queue */
		{
			free(pt);
			return (0);
		}

		return (1);							/* target found */
	}

	/* explore neighbors in all four directions */
	if (dfs(map, rows, cols, x + 1, y, tx, ty, vis, q) ||
		dfs(map, rows, cols, x, y + 1, tx, ty, vis, q) ||
		dfs(map, rows, cols, x - 1, y, tx, ty, vis, q) ||
		dfs(map, rows, cols, x, y - 1, tx, ty, vis, q))
	{
		pt = malloc(sizeof(*pt));
		if (!pt)
			return (0);
		pt->x = x;
		pt->y = y;
		if (!queue_push_front(q, pt))
		{
			free(pt);
			return (0);
		}
		return (1);
	}

	return (0);								/* target not found */
}

/**
 * alloc_vis - allocates a 2D array for visited cells
 * @rows:		number of rows
 * @cols:		number of columns
 *
 * Return:		pointer to the allocated array or NULL on failure
 */
char **alloc_vis(int rows, int cols)
{
	char **vis = NULL;							/* visited cells */
	int r;										/* row index */

	vis = malloc(sizeof(*vis) * rows);			/* allocate row pointers */
	if (!vis)
		return (NULL);

	for (r = 0; r < rows; r++)					/* allocate column pointers */
	{
		vis[r] = calloc((size_t)cols, sizeof(**vis));
		if (!vis[r])
		{
			free_vis(vis, r);
			return (NULL);
		}
	}

	return (vis);									/* return allocated array */
}

/**
 * free_vis -	frees the allocated memory for visited cells
 * @vis:		2D array of visited cells
 * @rows:		number of rows
 *
 * Return:		void
 */
void free_vis(char **vis, int rows)
{
	int r;										/* row index */

	if (!vis)
		return;

	for (r = 0; r < rows; r++)					/* free each row */
		free(vis[r]);

	free(vis);									/* free the array */
}

/**
 * backtracking_array -	finds a path from start to target using backtracking
 * @map:				the map
 * @rows:				number of rows in the map
 * @cols:				number of columns in the map
 * @start:				starting point
 * @target:				target point
 *
 * Return:				pointer to the queue of points in the path
 *						or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target)
{
	queue_t *q;									/* queue */
	char **vis;									/* visited cells */

	if (!map || !start || !target || rows <= 0 || cols <= 0)
		return (NULL);

	q = queue_create();							/* create the queue */
	if (!q)
		return (NULL);

	vis = alloc_vis(rows, cols);				/* allocate visited cells */
	if (!vis)
	{
		queue_delete(q);
		return (NULL);
	}

	if (!dfs(map, rows, cols, start->x, start->y,
			 target->x, target->y, vis, q))		/* start DFS */
	{
		queue_delete(q);
		q = NULL;
	}

	free_vis(vis, rows);
	return (q);									/* return the queue */
}
