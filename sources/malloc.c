/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 09:13:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/12 11:26:27 by mrajaona         ###   ########.fr       */
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

void		*malloc(size_t size)
{
	static int	sz = 0;
	void		*ptr;

	if (sz == 0)
		sz = getpagesize();
	ptr = NULL;
	return (ptr);
}
