//
// Created by Nathan on 18/01/18.
//

#include "malloc.h"

void		*reallocf(void *ptr, size_t size)
{
	void	*new_ptr;
	if (!(new_ptr = realloc(ptr, size)))
	{
		free(ptr);
		return (NULL);
	}
	return (new_ptr);
}