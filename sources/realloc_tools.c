/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 11:34:15 by mrajaona          #+#    #+#             */
/*   Updated: 2017/04/25 12:12:33 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Cherche la zone correspondant à l'adresse
** Retourne NULL si aucune zone ne correspond
*/
t_zone	*ft_fetch_zone(void *addr)
{
	t_head	*head;
	t_zone	*zone;

	if (!addr || !g_mem)
		return (NULL);
	head = g_mem->addr;
	while (head)
	{
		if ((zone = ft_search_zone(head->zones, addr)))
			return (zone);
		head = head->next;
	}
	return (NULL);
}

/*
** Cherche le header correspondant à la zone
** Retourne NULL si aucun header ne correspond
*/
t_head	*ft_fetch_head(t_zone *zone)
{
	t_head	*head;
	t_zone	*z;

	if (!zone || !g_mem)
		return (NULL);
	head = g_mem->addr;
	while (head)
	{
		if ((z = ft_search_zone(head->zones, zone->addr)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/*
** Retourne TRUE si il reste assez de place dans la zone réservée, FALSE sinon
*/
char	ft_zone_fit(size_t size, t_zone *zone)
{
	size_t	sz;
	t_head	*head;

	if (size <= zone->size)
		return (TRUE);
	if (zone->next)
		sz = (size_t)(zone->next->addr - zone->addr);
	else
	{
		head = ft_fetch_head(zone);
		size = head->size - (size_t)(head->zones - zone);
	}
	return (FALSE);
}
