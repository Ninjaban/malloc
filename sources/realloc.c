/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:20:32 by elemarch          #+#    #+#             */
/*   Updated: 2017/04/12 14:20:34 by elemarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//mnalloc une nouvelle zone puis copie le contenu de ptr dedans
static void	*realloc_copy(void *ptr, size_t size, size_t n)
{
	void *naddr;

	naddr = malloc(size);
	ft_memcpy(naddr, ptr, n);
	return (naddr);
}

// si !zone => NULL
// si ya de la place, agrandit / rétrécit le chiffre dans le header
//sinon, déplace, puis free
static void	*realloc_exec(ptr, size)
{
	t_zone	*cursor;
	void	*addr;

	cursor = ft_fetch_zone(ptr);
	if (ft_zone_fit(size, cursor))
	{
		cursor->size = size;
		addr = cursor->addr;
	}
	else
	{
		addr = realloc_copy(ptr, size, cursor->size);
		free(cursor->addr);
		cursor->addr = addr;
	}

	return (addr);
}

// si size = 0 => free(ptr)
// si !ptr => malloc(size)
// sinon => realloc exec
void		*realloc(void *ptr, size_t size)
{
	void	*new_zone;

	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		new_zone = malloc(size);
	else
		new_zone = realloc_exec(ptr, size);
	return (new_zone);
}