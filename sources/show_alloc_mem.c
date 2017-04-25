/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 09:13:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/25 15:43:35 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>

void			ft_print_total(size_t total)
{
	ft_putstr("Total : ");
	ft_putnbr_sizet(total);
	ft_putstr(" octets\n");
}

void			ft_print_zones(t_zone *zones, size_t *total)
{
	t_zone		*zone;

	zone = zones;
	if (zone->next)
		ft_print_zones(zone->next, &(*total));
	ft_print_address((size_t)zone->addr);
	ft_putstr(" - ");
	ft_print_address((size_t)(zone->addr + zone->size));
	ft_putstr(" : ");
	ft_putnbr_sizet(zone->size);
	ft_putstr(" octets\n");
	*total = *total + zone->size;
}

void			ft_print_head(t_head *head, size_t *total)
{
	char		*str;

	if (head->size / g_mem->sz <= TINY_ZONE)
		str = "TINY : ";
	else if (head->size / g_mem->sz <= SMALL_ZONE)
		str = "SMALL : ";
	else
		str = "LARGE : ";
	ft_putstr(str);
	ft_print_address((size_t)head);
	ft_putchar('\n');
	if (head->zones)
		ft_print_zones(head->zones, &(*total));
}

void			show_alloc_mem(void)
{
	t_head		*head;
	size_t		total;

	if (!g_mem)
		return ;
	head = g_mem->addr;
	total = 0;
	while (head)
	{
		ft_print_head(head, &total);
		head = head->next;
	}
	ft_print_total(total);
}
