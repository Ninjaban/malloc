/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:18:41 by mrajaona          #+#    #+#             */
/*   Updated: 2017/04/12 16:48:43 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** size_t *ft_zone_size(t_head plage, void *ptr)
**
** Variables :
** ptr		: zone a trouver
** plage	: adresse de la plage contenant la zone
**
** Description :
** Renvoie la taille de la zone.
*/

size_t	*ft_zone_size(t_head plage, void *ptr)
{
	t_zone	*zone;

	if (!plage)
		return (NULL); // ERROR
	zone = plage->zones;
	while (zone)
	{
		if (zone->addr == ptr)
			return (zone->size);
		zone = zone->next;
	}
	return (NULL); // INVALID_ADRESS
}

/*
** t_head *ft_find_plage(void *ptr)
**
** Variables :
** ptr		: zone a trouver
** g_mem	: informations sur la premiere plage
**
** Description :
** Trouve la plage correspondant a l'adresse recherchee.
*/

t_head	*ft_find_plage(void *ptr)
{
	t_head	*plage;
	t_zone	*zone;

	plage = (t_head *)(g_mem->addr);
	while (plage)
	{
		zone = plage->zones;
		while (zone)
		{
			if (zone->addr == ptr)
				return (plage);
			zone = zone->next;
		}
		plage = plage->next;
	}
	return (NULL); // INVALID_ADRESS
}

/*
** void ft_relink_zone(t_head *plage, void *ptr)
**
** Variables :
** ptr		: zone a trouver
** plage	: adresse de la plage contenant la zone
**
** Description :
** retire la zone de la liste
*/

void	ft_relink_zone(t_head plage, void *ptr)
{
	t_zone	*prev;
	t_zone	*next;
	t_zone	*zone;

	if (!plage)
		return (NULL); // ERROR
	zone = plage->zones;
	prev = NULL;
	while (zone)
	{
		if (zone->addr == ptr)
		{
			next = zone->next;
			(prev ? prev->next : plage->zones) = next;
			zone->addr = NULL;
			zone->size = 0;
			zone->next = NULL;
			return ;
		}
		prev = zone;
		zone = zone->next;
	}
	// INVALID_ADRESS;
}

/*
** void ft_plage_zone(t_head *ptr)
**
** Variables :
** ptr		: plage a trouver
** g_mem	: informations sur la premiere plage
**
** Description :
** retire la plage de la liste
*/

void	ft_relink_plage(t_head *ptr)
{
	t_head	*plage;

	plage = (t_head *)(g_mem->addr);
	prev = NULL;
	while (zone)
	{
		if (plage == ptr)
		{
			next = plage->next;
			if (prev)
				prev->next = next;
			else
				g_mem->addr = (void *)next;
			plage->next = NULL;
			plage->size = 0;
			plage->zones = NULL;
			return ;
		}
		prev = plage;
		plage = plage->next;
	}
}

/*
** void free(void *ptr)
**
** Variables :
** ptr	: adresse a liberer
**
** Description :
** Libere l'allocation de la memoire allouee  pointee par "ptr" et la set a 0.
** Si "ptr" vaut NULL, ne fait rien.
**
*/

void	free(void *ptr)
{
	size_t	size;
	size_t	n;
	t_head	*plage;

	if (!ptr)
		return ;
	if (!(plage = ft_find_plage(ptr)))
		return ; // INVALID_ADRESS
	size = ft_zone_size(ptr);
	ft_relink_zone(plage, ptr);
	n = 0;
	while (n < size)
	{
		ptr[n] = 0;
		n++;
	}
	if (!(plage->zones))
	{
		ft_relink_plage(plage);
		if (munmap(plage, sz) == -1)
			return ; // MUNMAP_ERROR
		plage = NULL;
	}
}
