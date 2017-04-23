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

t_mem		*g_mem = NULL;

static size_t	ft_getsize(size_t len)
{
	if (len <= TINY_ZONE)
		return ((size_t)g_mem->sz *
				((TINY_ZONE * 100 + HEADER * 101) / g_mem->sz + 1));
	else if (len <= SMALL_ZONE)
		return ((size_t)g_mem->sz *
				((SMALL_ZONE * 100 + HEADER * 101) / g_mem->sz + 1));
	else
		return ((size_t)g_mem->sz * (((len + HEADER * 2) / (size_t)g_mem->sz) + 1));
}

static size_t	ft_getsizeless(t_head *addr)
{
	t_zone	*zone;

	zone = addr->zones;
	while (zone->next)
		zone = zone->next;
	return ((size_t)(zone->addr - (void *)(zone + 1)));
}

static void		*ft_getnextzone(t_head *addr, size_t len)
{
	t_zone	*zone;

	zone = addr->zones;
	if (addr->size > len && ft_getsizeless(addr) >= sizeof(t_zone))
		while (zone)
		{
			if (zone->next && len <=
				(size_t)(zone->addr - (zone->next->addr + zone->next->size)))
				return (zone->next->addr + zone->next->size);
			else if (!zone->next && len + sizeof(t_zone) <=
			(size_t)((zone->addr + zone->size) - (void *)(zone + 1)))
			{
				return (zone->addr - len);
			}
			zone = zone->next;
		}
	return ((addr->next) ? ft_getnextzone(addr->next, len) : NULL);
}

#include <stdio.h>

static t_zone	*ft_newzone(void *headaddr, void *addr, size_t size)
{
	t_zone		*zone;

	zone = (t_zone *)headaddr;
	zone->size = size;
	zone->addr = addr;
	zone->next = NULL;
	return (zone);
}

static void		*ft_newhead(void *addr, size_t size, size_t zonelen)
{
	t_head		*head;
	t_head		*tmp;

	head = addr;
	head->size = size;
	head->next = NULL;
	head->zones = ft_newzone(addr + sizeof(t_head), addr + size - zonelen, zonelen);
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

	zone = ft_newzone(ztmp + 1, ptr, len);
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
		while (ztmp)
		{
			if (ztmp->addr - ((ztmp->next) ? ztmp->next->size : len) == ptr)
				return ft_structzone(ztmp, ptr, len);
			ztmp = ztmp->next;
		}
		tmp = tmp->next;
	}
}

void			*malloc(size_t len)
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
