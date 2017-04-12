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

t_mem			*g_mem = NULL;

static size_t	ft_getsize(size_t len)
{
	return (g_mem->sz * (len / g_mem->sz));
}

static void		*ft_getnextzone(void *addr, size_t len)
{
	t_zone *zone;

	zone = ((t_head *) addr)->zones;
	if (((t_head *) addr)->size <= len)
		while (zone)
		{
			if (zone->next && len <= (((t_zone *) (zone->next))->addr -
									  (zone->addr + zone->size)))
				return (zone->addr + zone->size);
			else if (!zone->next && len <=
									(addr + ((t_head *) addr)->size) -
									(zone->addr + zone->size))
				return (zone->addr + zone->size);
			zone = zone->next;
		}
	return ((((t_head *) addr)->next) ?
			ft_getnextzone(((t_head *) addr)->next, len) : NULL);
}

static t_zone	*ft_newzone(void *addr, size_t size)
{
	t_zone		zone;

	zone.size = size;
	zone.addr = addr;
	zone.next = NULL;
	return (&zone);
}

static void		*ft_newhead(void *addr, size_t size, size_t zonelen)
{
	t_head		head;
	t_head		*tmp;

	head.size = size;
	head.addr = addr;
	head.next = NULL;
	head.zones = ft_newzone(addr + HEADER, zonelen);
	if (!g_mem->addr)
	{
		write(1, "(null) 2", 8);
		g_mem->addr = &head;
	}
	else
	{
		tmp = g_mem->addr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = &head;
	}
	return (&head.zones->addr);
}

static void		ft_structzone(t_zone *ztmp, t_zone *zone)
{
	zone->next = ztmp->next;
	ztmp->next = zone;
}

static void		ft_addzone(void *addr, void *ptr, size_t len)
{
	t_head		*tmp;
	t_zone		*ztmp;
	t_zone		*zone;

	zone = ft_newzone(ptr, len);
	tmp = addr;
	while (tmp)
	{
		ztmp = tmp->zones;
		while (ztmp)
		{
			if (ztmp->addr + ztmp->size == ptr)
				return (ft_structzone(ztmp, zone));
			ztmp = ztmp->next;
		}
	}
}

void			*ft_malloc(size_t len)
{
	void		*addr;
	void		*plage;
	size_t		size;
	static char	bool = FALSE;

	if (!bool)
	{
		g_mem = ft_mem_init();
		bool = TRUE;
	}

	if (!g_mem)
		write(1, "(null) 1", 8);
	if (!g_mem->addr)
		write(1, "(null) 2", 8);

	if (g_mem->addr && (addr = ft_getnextzone(g_mem->addr, len)))
		ft_addzone(g_mem->addr, addr, len);
	else
	{
		write(1, "OK", 2);
		size = ft_getsize(len);
		plage = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
					 -1, 0);
		return (ft_newhead(plage, size, len));
	}
	return (addr);
}
