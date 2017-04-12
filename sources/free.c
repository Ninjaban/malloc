/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:18:41 by mrajaona          #+#    #+#             */
/*   Updated: 2017/04/12 13:59:36 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** void free(void *ptr)
**
** Variables :
** ptr	: pointeur vers l'adresse a liberer
**
** Description :
** Libere l'allocation de la memoire allouee  pointee par "ptr" et la set a 0.
** Si "ptr" vaut NULL, ne fait rien.
*/

/*
** Fonctions appelees :
** int ft_GETLASIZE(void *addr)
** 	renvoie la taille de memoire allouee a l'adresse "ptr"
**
** int munmap(void *addr, size_t len)
** 	<sys/mman.h>
** 	success : 0 ; falure : -1, set errno
** 	"addr" must be a multiple of the page size
** 	"len" is the length of the mapping in bytes ?
*/

int		ft_empty_page(void *addr) // debut ? header ?
{
	size_t	n;

	n = 0;
	while (DANS_LA_PAGE) // n < sz ?
	{
		if (val != 0)
			return (FALSE);
		n++;
	}
	return (TRUE);
}

void	free(void *ptr)
{
	size_t	len; // n'inclut pas le header
	size_t	n;
	void	*page;
	int		sz; // = getpagesize() ?

	if (!ptr)
		return ;
	len = ft_GETLASIZE(ptr);
	link_prev_next_zone();
	set_ptr_header_to_0();
	n = 0;
	while (n < len)
	{
		ptr[n] = 0;
		n++;
	}
	if (ft_empty_page(page))
	{
		link_prev_next_page(page);
		set_page_header_to_0(page);
		set_page_end_to_0(page);
		munmap(page, sz);
	}
}
