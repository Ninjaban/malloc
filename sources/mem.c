/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:31:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/25 15:43:09 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone		*ft_mem_get_zone(void *addr)
{
	t_head	*sheet;
	t_zone	*current;

	if (addr == NULL)
		return (NULL);
	sheet = g_mem->addr;
	while (sheet)
	{
		current = sheet->zones;
		while (current && current->addr != addr)
			current = current->next;
		if (current)
			return (current);
		sheet = sheet->next;
	}
	return (NULL);
}

/*
** FONCTION :: ft_mem_get_size
**  Renvoie la taille de la zone mémoire pointée
**
** PARAMETRES
**  void*	addr		pointeur vers l'adresse dont on veut la taille
**
** VALEUR DE RETOUR (size_t)
**  renvoie 0 si la zone est free ou inexistante, renvoie sa taille sinon.
*/

size_t		ft_mem_get_size(void *addr)
{
	t_zone	*zone;

	zone = ft_mem_get_zone(addr);
	if (zone)
		return (zone->size);
	else
		return (0);
}

//initialise la variable globale

t_mem		*ft_mem_init(void)
{
	t_mem	*mem;

	FT_DEBUG("Start %s", "");
	mem = mmap(0, (size_t)getpagesize(), PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANON, -1, 0);
	mem->addr = NONE;
	mem->sz = getpagesize();
	FT_DEBUG("End %s", "");
	return (mem);
}
