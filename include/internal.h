/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 09:48:00 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/31 13:16:00 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FICHIER :: HEADER
** 	Dans l'intégralité du projet sont nommés :
** 	- ta la taille allouée demandée
** 	- sz le retour de getPageSize()
*/

#ifndef INTERNAL_H
# define INTERNAL_H

/*
** INCLUDES
*/

# include <unistd.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <pthread.h>

/*
** STRUCTURE :: zone
**  Structure contenant l'addresse et la taille d'une zone mémoire allouée
**
** VARIABLES
**	void*			addr		addresse du début de la mémoire réservée
**	int				size		taille de la zone
**	void*			next		addresse de la prochaine structure
*/

typedef struct		s_zone
{
	void			*addr;
	size_t			size;
	struct s_zone	*next;
}					t_zone;

/*
** STRUCTURE :: head
**  Structure stockée dans le header de chaque plage mémoire réservée
**
** VARIABLES
**	void*			next		addresse du début de la mémoire réservée
**	int				size		taille de la zone
**	t_zone*			zones		lien vers la liste des zones mémoires réservées
*/

typedef struct		s_head
{
	size_t			size;
	t_zone			*zones;
	struct s_head	*next;
}					t_head;

/*
** STRUCTURE :: sys
**  Structure d'information utilisée par toute la lib
**
** VARIABLES
**	void*			addr		addresse du début de la mémoire réservée
**	int				sz			retour de getpagesize()
*/

typedef struct		s_mem
{
	int				sz;
	t_head			*addr;
}					t_mem;

/*
** GLOBAL
*/

extern t_mem		*g_mem;

/*
** DEFINES :: BASICS
**  TRUE/FALSE		valeurs 1 et 0
*/

# define TRUE		1
# define FALSE		0

# define NONE		((void *)-1)

/*
** DEFINES :: PAGE_SIZES
**  HEADER			sizeof(void*). Taille des zones réservées
**  TINY_ZONE		zone minimum lors des appels de mamalloc
**  SMALL_ZONE		zone minimum lorsqu'une taille est supérieure à TINY_MAX
**  TINY_MAX		taille maximum d'un TINY pour une allocation de TINY_ZONE
**  SMALL_MAX		taille maximum d'un SMALL pour une allocation de SMALL_ZONE
*/

# define MULTI		23

# define HEADER		(size_t)24
# define HEADER_MAX	(size_t)(HEADER * (MULTI + 1))
# define TINY_ZONE	1024
# define SMALL_ZONE	(TINY_ZONE * MULTI)
# define TINY_MAX	(TINY_ZONE * MULTI)
# define SMALL_MAX	(SMALL_ZONE * MULTI)

/*
** PROTOTYPES
*/

void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putnbr_sizet(size_t nbr);
void				ft_print_address(size_t addr);

t_zone				*ft_search_zone(t_zone *zones, void *ptr);
t_zone				*ft_fetch_zone(void *addr);
char				ft_zone_fit(size_t size, t_zone *zone);
void				*ft_memcpy(void *dst, const void *src, size_t n);
t_mem				*ft_mem_init(void);

size_t				ft_getsize(size_t len);
t_zone				*ft_newzone(void *headaddr, void *addr, size_t size);
void				ft_moveheaderzonerec(t_zone *zone);
void				ft_structzone(t_zone *ztmp, void *ptr, size_t len);

void				ft_free(void *ptr);
void				*ft_malloc(size_t size);
void				*ft_realloc(void *ptr, size_t size);
void				ft_show_alloc_mem(void);

#endif
