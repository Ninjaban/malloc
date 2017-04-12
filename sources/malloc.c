/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 09:13:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/12 12:13:33 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** void *malloc(size_t size)
**
** size	: taille de memoire a allouer
**
** Alloue "size" octets de memoire et retourne un pointeur sur la memoire allouee.
** En cas d'erreur, retourne NULL.
*/

static size_t	ft_getsize(void)
{

}

void			*malloc(size_t len)
{
	void	*addr;
	size_t	size;

	g_mem = ft_mem_init();

	size = ft_getsize();

	addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
}
