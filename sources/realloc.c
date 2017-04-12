/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:20:10 by mrajaona          #+#    #+#             */
/*   Updated: 2017/04/12 11:32:23 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** void *realloc(void *ptr, size_t size)
**
** ptr	: pointeur vers l'adresse memoire a reallouer
** size	: taille de memoire a allouer
**
** Essaie de modifier la taille de l'allocation pointee par "ptr" a "size"
** octets, et retourne "ptr".
** S'il n'y a pas assez de place a l'emplacement pointe par "ptr", cree une
** nouvelle allocation, y copie autant de donnees de l'ancienne allocation que
** possible dans la limite de la taille de la nouvelle allocation, libere
** l'ancienne allocation et retourne un pointeur sur cette nouvelle allocation.
** Si La nouvelle taille est inferieure a la precedente, set la memoire non
** utilisee a 0.
** En cas d'erreur, retourne NULL.
*/

void	*realloc(void *ptr, size_t size)
{
	return (ptr);
}
