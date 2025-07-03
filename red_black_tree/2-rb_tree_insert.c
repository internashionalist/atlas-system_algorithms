#include "rb_trees.h"

/**
 * rotate_left - rotates the subtree rooted at x to the left
 * @root:		double pointer to tree root (may change)
 * @x:			pivot node (whose right child becomes the new parent)
 *
 * Return:		void
 */
void rotate_left(rb_tree_t **root, rb_tree_t *x)
{
	rb_tree_t *y;

	y = x->right;						/* y becomes new parent */
	x->right = y->left;					/* move y’s left subtree */
	if (y->left)						/* re‑parent left subtree (if any) */
		y->left->parent = x;

	y->parent = x->parent;				/* link y to x’s former parent */
	if (!x->parent)						/* if x is root, update root ptr */
		*root = y;
	else if (x == x->parent->left)		/* if x is a left child*/
		x->parent->left = y;			/* link y as that left child */
	else
		x->parent->right = y;			/* else link y as right child */

	y->left = x;						/* place x on y’s left */
	x->parent = y;						/* re‑parent x */
}

/**
 * rotate_right - rotates the subtree rooted at y to the right
 * @root:		double pointer to tree root (may change)
 * @y:			pivot node whose left child becomes the new parent
 *
 * Return:		void
 */
void rotate_right(rb_tree_t **root, rb_tree_t *y)
{
	rb_tree_t *x;						/* ptr to pivot node */

	x = y->left;						/* x becomes new parent */
	y->left = x->right;					/* move x’s right subtree */
	if (x->right)						/* re‑parent right subtree (if any) */
		x->right->parent = y;

	x->parent = y->parent;				/* link x to y’s former parent */
	if (!y->parent)						/* if y is root, update root ptr */
		*root = x;
	else if (y == y->parent->left)		/* if y is a left child */
		y->parent->left = x;			/* link x as that left child */
	else
		y->parent->right = x;			/* else link x as right child */

	x->right = y;						/* place y on x’s right */
	y->parent = x;						/* re‑parent y */
}

/**
 * bst_insert - inserts value into a BST
 * @root:		double pointer to tree root
 * @value:		value to insert
 *
 * Return:		pointer to the new (RED) node, or NULL on failure/duplicate
 */
rb_tree_t *bst_insert(rb_tree_t **root, int value)
{
	rb_tree_t *parent = NULL;				/* ptrs for walking tree */
	rb_tree_t *curr = *root;
	rb_tree_t *node;

	while (curr)							/* loop til insertion point */
	{
		parent = curr;						/* track parent */
		if (value < curr->n)				/* if value less than current */
			curr = curr->left;				/* go left */
		else if (value > curr->n)			/* if value greater than current */
			curr = curr->right;				/* go right */
		else
			return (NULL);					/* duplicate value */
	}

	node = rb_tree_node(parent, value, RED); /* allocate red node */
	if (!node)
		return (NULL);

	if (!parent)							/* new root */
		*root = node;
	else if (value < parent->n)				/* if value less than parent */
		parent->left = node;				/* link as left child */
	else
		parent->right = node;				/* else link as right child */

	return (node);							/* return pointer to new node */
}

/**
 * rebalance_left - handles fix‑up when parent is a left child
 * @root:			double pointer to tree root
 * @z:				address of the current node pointer (may move up the tree)
 *
 * Return:			void
 */
void rebalance_left(rb_tree_t **root, rb_tree_t **z)
{
	rb_tree_t *p;							/* parent of z */
	rb_tree_t *g;							/* grandparent of z */
	rb_tree_t *u;							/* uncle of z */

	p = (*z)->parent;
	g = p->parent;
	u = g->right;

	if (u && u->color == RED)				/* uncle is RED */
	{
		p->color = BLACK;					/* parent becomes BLACK */
		u->color = BLACK;					/* uncle becomes BLACK */
		g->color = RED;						/* grandparent becomes RED */
		*z = g;								/* move up */
	}
	else									/* uncle is BLACK or NULL */
	{
		if (*z == p->right)					/* current is right child */
		{
			*z = p;							/* move current up */
			rotate_left(root, p);			/* rotate left on parent */
			p = (*z)->parent;				/* reassign parent */
			g = p->parent;					/* reassign grandparent */
		}
		p->color = BLACK;					/* parent becomes BLACK */
		g->color = RED;						/* grandparent becomes RED */
		rotate_right(root, g);				/* rotate right on grandparent */
	}
}

/**
 * rebalance_right - handles fix‑up when parent is a right child
 * @root:			double pointer to tree root
 * @z:				address of the current node pointer (may move up the tree)
 *
 * Return: Nothing
 */
void rebalance_right(rb_tree_t **root, rb_tree_t **z)
{
	rb_tree_t *p;							/* parent of z */
	rb_tree_t *g;							/* grandparent of z */
	rb_tree_t *u;							/* uncle of z */

	p = (*z)->parent;
	g = p->parent;
	u = g->left;

	if (u && u->color == RED)				/* uncle is RED */
	{
		p->color = BLACK;					/* parent becomes BLACK */
		u->color = BLACK;					/* uncle becomes BLACK */
		g->color = RED;						/* grandparent becomes RED */
		*z = g;								/* move up */
	}
	else									/* uncle is BLACK or NULL */
	{
		if (*z == p->left)					/* current is left child */
		{
			*z = p;							/* move current up */
			rotate_right(root, p);			/* rotate right on parent */
			p = (*z)->parent;				/* reassign parent */
			g = p->parent;					/* reassign grandparent */
		}
		p->color = BLACK;					/* parent becomes BLACK */
		g->color = RED;						/* grandparent becomes RED */
		rotate_left(root, g);				/* rotate left on grandparent */
	}
}

/**
 * rebalance - restore Red‑Black properties after insertion
 * @root:		double pointer to tree root
 * @z:			newly inserted node
 *
 * Return:		void
 */
void rebalance(rb_tree_t **root, rb_tree_t *z)
{
	/* loop until root or black parent */
	while (z != *root && z->parent->color == RED)
	{
		if (z->parent == z->parent->parent->left) /* parent is left child */
			rebalance_left(root, &z);
		else
			rebalance_right(root, &z);			/* parent is right child */
	}
	(*root)->color = BLACK;						/* root always black */
}

/**
 * rb_tree_insert - inserts value into a Red‑Black tree
 * @tree:		double pointer to root
 * @value:		value to insert
 *
 * Return:		pointer to the created node, or NULL on failure/duplicate
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *node;					/* pointer to new node */

	if (!tree)							/* NULL tree pointer check */
		return (NULL);

	node = bst_insert(tree, value);		/* insert into BST */
	if (!node)							/* check for failure/duplicate */
		return (NULL);

	rebalance(tree, node);				/* restore Red‑Black properties */

	return (node);						/* return pointer to the new node */
}
