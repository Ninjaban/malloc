/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 09:29:00 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/17 15:06:20 by jcarra           ###   ########.fr       */
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
			return (zone);
		zone = zone->next;
	}
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
		tmp->next = head->next;
	}
	munmap((void *)head, head->size);
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
	head = g_mem->addr;
	while (head != NONE)
	{
		if ((zone = ft_search_zone(head->zones, ptr)))
		{
			ft_clear_zone(head, zone);
			if (head->zones == NONE && head->next != NONE &&
				head->next->zones == NONE)
				ft_delete_head(head);
			if (g_mem->addr == NONE)
			{
				munmap(g_mem, (size_t)g_mem->sz);
				g_mem = NONE;
			}
			return ;
		}
		head = head->next;
	}
}
