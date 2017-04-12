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

/*
** DEFINES :: PAGE_SIZES
** 	TINY		ta <= sz
** 	SMALL		ta <= sz*4
** 	LARGE		ta <= sz*100
*/

# define TINY	1
# define SMALL	4
# define LARGE	100

/*
** PROTOTYPES
*/

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem();

#endif
