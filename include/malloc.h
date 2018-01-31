
#ifndef MALLOC_MALLOC_H
# define MALLOC_MALLOC_H

# include "stdlib.h"

void				free(void *ptr);
void				*malloc(size_t size);
void				*calloc(size_t nmemb, size_t size);
void				*realloc(void *ptr, size_t size);
void				*reallocf(void *ptr, size_t size);
void				show_alloc_mem(void);

#endif
