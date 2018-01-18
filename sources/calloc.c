//
// Created by Nathan on 18/01/18.
//

#include "malloc.h"

void		*calloc(size_t nmemb, size_t size)
{
	return (malloc(nmemb * size));
}