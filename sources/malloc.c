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

t_mem		*g_mem = NULL;

static size_t	ft_getsize(size_t len)
{
	return (g_mem->sz * ((len < g_mem->sz) ? 1 : len / g_mem->sz + 1));
}

static void		*ft_getnextzone(t_head *addr, size_t len)
{
	t_zone *zone;

	zone = addr->zones;
		printf("%zu | %zu\n", addr->size, len);
	if (addr->size - HEADER >= len)
		while (zone)
		{
			if (zone->next && len <= zone->next->addr -
											(zone->addr + zone->size))
				return (zone->addr + zone->size);
			else if (!zone->next && len <= ((void *)addr + addr->size) -
										(zone->addr + zone->size))
			{
				printf("OK\n");
				return (zone->addr + zone->size);
			}
			zone = zone->next;
		}
	return ((addr->next) ? ft_getnextzone(addr->next, len) : NULL);
}

static t_zone	*ft_newzone(void *headaddr, void *addr, size_t size)
{
	t_zone		*zone;

	zone = (t_zone *)headaddr;
	printf("ZONE : %p\n", zone);
	zone->size = size;
	zone->addr = addr;
	zone->next = NULL;
	return (zone);
}

static void		*ft_newhead(void *addr, size_t size, size_t zonelen)
{
	t_head		*head;
	t_head		*tmp;

	static size_t nb = 0;
	nb = nb + 1;
//	printf("%zu\n", nb);

	head = (t_head *)addr;
	head->size = size;
	head->next = NULL;
	head->zones = ft_newzone(addr + sizeof(t_head), addr + HEADER, zonelen);
	printf("head size : %zu\n", head->size);
	printf("t_zone : %zu\n", sizeof(t_zone));
	printf("t_head : %zu\n", sizeof(t_head));
	printf("START : %p\n", head);
	printf("END : %p\n", head + head->size);
	if (g_mem->addr)
	{
		tmp = g_mem->addr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = head;
	}
	else
		g_mem->addr = head;
	return (head->zones->addr);
}

static void		ft_structzone(t_zone *ztmp, void *ptr, size_t len)
{
	t_zone		*zone;

	printf("ZONE PREV : %zu\n", ztmp);
	printf("ZONE NEXT : %zu\n", ztmp + sizeof(t_zone));
	printf("ZONE NEXT : %zu\n", ztmp + 1);
	printf("T_ZONE : %zu\n", sizeof(t_zone));
	zone = ft_newzone(ztmp + sizeof(t_zone), ptr, len);
	zone->next = ztmp->next;
	ztmp->next = zone;
}

static void		ft_addzone(t_head *addr, void *ptr, size_t len)
{
	t_head		*tmp;
	t_zone		*ztmp;

	tmp = addr;
	while (tmp)
	{
		ztmp = tmp->zones;
		while (ztmp->addr)
		{
			if (ztmp->addr + ztmp->size == ptr)
				return ft_structzone(ztmp, ptr, len);
			ztmp = ztmp->next;
		}
	}
}

void			*ft_malloc(size_t len)
{
	void		*addr;
	void		*plage;
	size_t		size;

	if (!g_mem)
		g_mem = ft_mem_init();

	if (g_mem->addr && (addr = ft_getnextzone(g_mem->addr, len)))
			ft_addzone(g_mem->addr, addr, len);
	else
	{
		size = ft_getsize(len);
		if ((plage = mmap(0, size, PROT_READ | PROT_WRITE,
						  MAP_PRIVATE | MAP_ANON, -1, 0)) != (void *)-1)
			return (ft_newhead(plage, size, len));
		else
			return (NULL);
	}
	return (addr);
}
