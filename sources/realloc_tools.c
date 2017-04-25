/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 11:34:15 by mrajaona          #+#    #+#             */
/*   Updated: 2017/04/25 11:34:16 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Chea
** Retourne NULL si aucune zone ne correspond
*/

t_zone	*ft_fetch_zone(void *addr)
{
	t_head	header;
	t_zone	zone;

	if (!addr || !g_mem)
		return (NULL);
	header = g_mem->addr;
	while (head)
	{
		if ((zone = ft_search_zone(head->zones, ptr)))
			return (zone);
		head = head->next;
	}
	return (NULL);
}
