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
#include <malloc.h>

/* ************************************************************************** */

t_zone			*ft_search_zone(t_zone *zones, void *ptr)
{
	t_zone		*zone;

	zone = zones;
	while (zone)
	{
		if (zone->addr == ptr)
			return (zone);
		zone = zone->next;
	}
	return (NULL);
}

void			ft_clear_zone(t_head *head, t_zone *zone)
{
	if (head->zones == zone && !zone->next)
		head->zones = NULL;
	else
		while (zone->next)
			if (!zone->next->next)
				zone->next = NULL;
			else
			{
				zone->addr = zone->next->addr;
				zone->size = zone->next->size;
				zone = zone->next;
			}
}

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
	munmap(head, head->size);
}

void			free(void *ptr)
{
	t_head	*head;
	t_zone	*zone;

	if (!ptr || !g_mem)
		return ;
	head = g_mem->addr;
	while (head)
	{
		if ((zone = ft_search_zone(head->zones, ptr)))
		{
			ft_clear_zone(head, zone);
			if (!head->zones)
				ft_delete_head(head);
			if (!g_mem->addr)
				munmap(g_mem, (size_t)g_mem->sz);
			return ;
		}
		head = head->next;
	}
}