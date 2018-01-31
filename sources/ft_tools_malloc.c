/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:54:01 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/31 12:57:11 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

/*
**	Récupère la taille en octets de mémoire à alouer.
**
**	La valeur retourné sera obligatoirement un multiple de getpagesize();
**
**	La valeur retourné sera calculé en fonction de la taille demander par
**	l'utilisateur. Dans le cas d'un TINY ou d'un SMALL, on prevois une plage
**	pouvant contenir 100 TINY ou SMALL ainsi que 100 header de zone et 1 header
**	de plage.
*/

size_t			ft_getsize(size_t len)
{
	if (len <= TINY_MAX)
		return ((size_t)g_mem->sz *
				((TINY_MAX + HEADER_MAX) / g_mem->sz + 1));
	else if (len <= SMALL_MAX)
		return ((size_t)g_mem->sz *
				((SMALL_MAX + HEADER_MAX) / g_mem->sz + 1));
	else
		return ((size_t)g_mem->sz * (((len + HEADER * 2) /
									(size_t)g_mem->sz) + 1));
}

/*
**	Crée une nouvelle zone dont le header se trouvera à l'adresse @headaddr, la
**	zone de l'utilisateur se trouvera à l'adresse @addr et la taille sera @size.
**
**	@param headaddr
**	@param addr
**	@param size
**	@return
*/

t_zone			*ft_newzone(void *headaddr, void *addr, size_t size)
{
	t_zone		*zone;

	zone = (t_zone *)headaddr;
	zone->size = size;
	zone->addr = addr;
	zone->next = NONE;
	return (zone);
}

/*
**	Déplace un header de zone @zone une case plus loin.
*/

static void		ft_moveheaderzone(t_zone *zone, t_zone *next)
{
	void	*ptr;
	size_t	len;

	ptr = zone->addr;
	len = zone->size;
	zone = zone + 1;
	zone->size = len;
	zone->addr = ptr;
	zone->next = next;
}

/*
**	Déplace tout les maillon récursivement une case plus loin de partant du
**	dernier header de zone et en remontant jusqu'au premier header utilisé.
*/

void			ft_moveheaderzonerec(t_zone *zone)
{
	if (zone != NONE)
	{
		if (zone->next != NONE)
			ft_moveheaderzonerec(zone->next);
		ft_moveheaderzone(zone, ((zone->next != NONE) ? zone->next + 1 : NONE));
	}
}

/*
**	Crée une nouvelle zone dont le header se trouvera après le header @ztmp, la
**	zone de l'utilisateur se trouvera à l'adresse @ptr et sa taille sera @len.
**
**	Ajoute ensuite ce header de zone dans la liste des header de zone en
**	fonction de la position de la zone d'utilisateur:
**
**	Si la zone de l'utilisateur @ptr est la 3eme zone de la plage, alors le
**	header de zone sera le 3eme de la liste.
**
**	Cela permet de garder une liste de header et de zone ordonné et cohérente
**	lors d'une éventuelle lecture avec show_alloc_mem.
**
**	@param ztmp
**	@param ptr
**	@param len
*/

void			ft_structzone(t_zone *ztmp, void *ptr, size_t len)
{
	t_zone		*zone;

	ft_moveheaderzonerec(ztmp->next);
	zone = ft_newzone(ztmp + 1, ptr, len);
	zone->next = (ztmp->next != NONE) ? ztmp->next + 1 : NONE;
	ztmp->next = zone;
}
