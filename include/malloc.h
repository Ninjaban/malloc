/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 09:48:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/12 09:48:00 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FICHIER :: HEADER
** 	Dans l'intégralité du projet sont nommés :
** 	- ta la taille allouée demandée
** 	- sz le retour de getPageSize()
*/

#ifndef MALLOC_H
# define MALLOC_H

/*
** INCLUDES
*/

# include <unistd.h>
# include <stdlib.h>
# include <sysmman.h>

/*
** DEFINES :: BASICS
**  TRUE/FALSE		valeurs 1 et 0
*/

# define TRUE		1
# define FALSE		0

/*
** DEFINES :: PAGE_SIZES
**  HEADER			sizeof(void*). Taille des zones réservées
**  TINY_ZONE		zone minimum lors des appels de mamalloc
**  SMALL_ZONE		zone minimum lorsqu'une taille est supérieure à TINY_MAX
**  TINY_MAX		taille maximum d'un TINY pour une allocation de TINY_ZONE
**  SMALL_MAX		taille maximum d'un SMALL pour une allocation de SMALL_ZONE
*/

# define HEADER		8
# define TINY_ZONE	sz
# define SMALL_ZONE	TINY_ZONE * 100
# define TINY_MAX	((TINY_ZONE - HEADER * 2) / 100) - 8
# define SMALL_MAX	TINY_ZONE

/*
 * STRUCTURE :: sys
 *  Structure d'information utilisée par toute la lib
 *
 * VARIABLES
 *	void*			addr		addresse du début de la mémoire réservée
 *	int				sz			retour de getpagesize()
 */

typedef struct		s_mem
{
	void			*addr;
	int				sz;
}					t_mem;

/*
** PROTOTYPES
*/

t_mem				ft_mem_init(void);
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();

/*
** GLOBAL
*/

extern t_mem		*g_mem;

#endif
