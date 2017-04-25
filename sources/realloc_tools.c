/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 11:34:15 by mrajaona          #+#    #+#             */
/*   Updated: 2017/04/25 15:37:16 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Cherche la zone correspondant à l'adresse
** Retourne NULL si aucune zone ne correspond
*/

t_zone			*ft_fetch_zone(void *addr)
{
	t_head		*head;
	t_zone		*zone;

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

static t_head	*ft_fetch_head(t_zone *zone)
{
	t_head		*head;
	t_zone		*z;

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

char			ft_zone_fit(size_t size, t_zone *zone)
{
	t_head		*head;

	if (size <= zone->size)
		return (TRUE);
	if (zone->next)
		return (size <= (size_t)(zone->next->addr - zone->addr) ? TRUE : FALSE);
	head = ft_fetch_head(zone);
	return (size <= (head->size - (size_t)(zone->addr - head->zones->addr)) ?
			TRUE : FALSE);
}

/*
** Copie une zone memoire de taille n
*/

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	while (n)
	{
		*(d + n - 1) = *(s + n - 1);
		n--;
	}
	return (dst);
}
