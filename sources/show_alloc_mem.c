/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 09:13:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/12 09:13:00 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>

void			ft_print_total(size_t total)
{
	printf("Total : %zu octets\n", total);
}

void			ft_print_zones(t_zone *zones, size_t *total)
{
	t_zone		*zone;

	zone = zones;
	while (zone)
	{
		printf("%p - %p : %zu octets\n", zone->addr, zone->addr + zone->size,
				zone->size);
		*total = *total + zone->size;
		zone = zone->next;
	}
}

void			ft_print_head(t_head *head, size_t *total)
{
	char		*str;

	if (head->size / g_mem->sz <= TINY_ZONE)
		str = "TINY";
	else if (head->size / g_mem->sz <= SMALL_ZONE)
		str = "SMALL";
	else
		str = "LARGE";
	printf("%s : %p\n", str, head);
	ft_print_zones(head->zones, &(*total));
}

void			show_alloc_mem(void)
{
	t_head		*head;
	size_t		total;

	head = g_mem->addr;
	total = 0;
	while (head)
	{
		ft_print_head(head, &total);
		head = head->next;
	}
	ft_print_total(total);
}