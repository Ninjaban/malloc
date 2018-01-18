/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:31:00 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/17 15:08:58 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	initialise la variable globale
*/

t_mem		*ft_mem_init(void)
{
	t_mem	*mem;

	mem = mmap(0, (size_t)getpagesize(), PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANON, -1, 0);
	mem->addr = NONE;
	mem->sz = getpagesize();
	return (mem);
}
