#include "huffman.h"

/**
 * symbol_create -	creates a symbol_t structure
 * @data:			character to store in the symbol
 * @freq:			frequency associated with the symbol
 *
 * Return:			pointer to the created symbol or NULL on failure
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *s;				/* pointer to symbol structure */

	s = malloc(sizeof(*s));		/* allocate memory for symbol */
	if (s == NULL)
		return (NULL);

	s->data = data;				/* set character data */
	s->freq = freq;				/* set frequency */

	if (s->freq == 0)			/* check if frequency is zero */
	{
		free(s);				/* free memory if so */
		return (NULL);
	}

	return (s);					/* return pointer to symbol */
}
