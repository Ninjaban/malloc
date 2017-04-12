/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:18:41 by mrajaona          #+#    #+#             */
/*   Updated: 2017/04/12 12:01:38 by mrajaona         ###   ########.fr       */
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
** Fonctions appellees :
** int munmap(void *addr, size_t len)
** 	<sys/mman.h>
** 	success : 0 ; falure : -1, set errno
** 	"addr" must be a multiple of the page size
** 	"len" is the length of the mapping
*/

void	free(void *ptr)
{
	if (!ptr)
		return ;
	/* set all to 0 */
	/* unmap */
}
