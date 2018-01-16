/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 09:29:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/17 09:29:00 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"


/*
**	Cherche dans une plage un header de zone dont la zone corresponds à @ptr.
**
**	Renvois la zone trouvé, ou NULL si aucun header ne corresponds.
**
**	@param zones
**	@param ptr
**	@return zone
*/

t_zone			*ft_search_zone(t_zone *zones, void *ptr)
{
	t_zone		*zone;

	zone = zones;
	while (zone != NONE)
	{
		if (zone->addr == ptr)
		{
			FT_DEBUG("Zone %p Addr %p Next %p Ptr %p", zone, zone->addr, zone->next, ptr);
			return (zone);
		}
		zone = zone->next;
	}
	FT_DEBUG("End %s", "Not found");
	return (NULL);
}

/*
**	supprime le header de zone @zone dans la plage @head.
**
**	Afin d'évité les trous entre les headers de zone, remonte d'un cran les
**	informations des header suivant.
**
**	@param head
**	@param zone
*/

void			ft_clear_zone(t_head *head, t_zone *zone)
{
	if (head->zones == zone && zone->next == NONE)
	{
		head->zones = NONE;
		return ;
	}
	while (zone->next != NONE)
	{
		zone->addr = zone->next->addr;
		zone->size = zone->next->size;
		if (zone->next->next == NONE)
			zone->next = NONE;
		else
			zone = zone->next;
	}
}

/*
**	Delete la plage @head.
**
**	@param head
*/

void			ft_delete_head(t_head *head)
{
	t_head		*tmp;

	if (g_mem->addr == head)
		g_mem->addr = head->next;
	else
	{
		tmp = g_mem->addr;
		while (tmp->next != head)
			tmp = tmp->next;
		FT_DEBUG("head %p next %p", head, head->next);
		tmp->next = head->next;
	}
	FT_DEBUG("---   MUNMAP() PLAGE START = %p PLAGE END = %p size %zu", head, (void *)head + head->size, head->size);
	if (munmap((void *)head, head->size) == -1)
		FT_ERROR("munmap() failed %s", "");
}

/*
**	Vérifie si ptr et g_mem existe.
**
**	Si oui, cherche ptr dans les plages grace à search_zone();
**
**	Une fois trouvé, supprime la zone avec clear_zone();
**
**	Si la plage ne contiens plus aucune zone, supprime la plage avec
**	delete_head();
**	
**	@param ptr
*/

void			free(void *ptr)
{
	t_head	*head;
	t_zone	*zone;

	if (!ptr || g_mem == NONE)
		return ;
	FT_DEBUG("Free %p", ptr);
	head = g_mem->addr;
	while (head != NONE)
	{
		if ((zone = ft_search_zone(head->zones, ptr)))
		{
			FT_DEBUG("Clear zone %p in head %p", zone, head);
			ft_clear_zone(head, zone);
			if (head->zones == NONE)
				ft_delete_head(head);
			if (g_mem->addr == NONE)
			{
				if (munmap(g_mem, (size_t) g_mem->sz) == -1)
					FT_ERROR("munmap() failed %s", "");
				g_mem = NONE;
			}
			return ;
		}
		head = head->next;
	}
	FT_WARNING("End %s", "Not found");
}
