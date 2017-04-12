/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:20:32 by elemarch          #+#    #+#             */
/*   Updated: 2017/04/12 16:27:47 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//mnalloc une nouvelle zone puis copie le contenu de ptr dedans
static void	*realloc_copy(void *ptr, size_t size)
{
	void	*new_zone;
	int		i;

	i = 0;
	new_zone = malloc(size);
	while (i < size)
	{
		*(new_zone + i) = *(ptr + i);
		i++;
	}
	return (new_zone);
}

// si !zone => NULL
// si ya de la place, agrandit le chiffre dans le header
//sinon, déplace, puis free
static void	*realloc_exec(ptr, size)
{
	t_zone	*zone;
	void	*new_zone;

	zone = ft_mem_get_zone(addr);
	if (!zone)
		return (NULL);
	if (size <= (((t_zone *)(zone->next))->addr - (zone->addr + zone->size)))
	{
		zone->size = size;
		return (zone->addr);
	}
	new_zone = realloc_copy(ptr, size);
	free(ptr);
	return (new_zone);
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
