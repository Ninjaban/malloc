/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:20:32 by elemarch          #+#    #+#             */
/*   Updated: 2018/02/01 11:39:32 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

/*
**	mnalloc une nouvelle zone puis copie le contenu de ptr dedans
*/

static void	*realloc_copy(void *ptr, size_t size, size_t n)
{
	void *naddr;

	if (!(naddr = malloc(size)))
		return (NULL);
	ft_memcpy(naddr, ptr, n);
	return (naddr);
}

/*
**	si !zone => NULL
**	si ya de la place, agrandit / rétrécit le chiffre dans le header
**	sinon, déplace, puis free
*/

static void	*realloc_exec(void *ptr, size_t size)
{
	t_zone	*cursor;
	void	*addr;

	if (!(cursor = ft_fetch_zone(ptr)))
		return (NULL);
	if (ft_zone_fit(size, cursor))
	{
		cursor->size = size;
		addr = cursor->addr;
	}
	else
	{
		if (!(addr = realloc_copy(ptr, size, cursor->size)))
			return (NULL);
		free(cursor->addr);
		cursor->addr = addr;
	}
	return (addr);
}

/*
**	si size = 0 => free(ptr)
**	si !ptr => malloc(size)
**	sinon => realloc exec
*/

void		*ft_realloc(void *ptr, size_t size)
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
