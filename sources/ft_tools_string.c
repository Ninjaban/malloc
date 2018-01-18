/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 09:13:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/25 15:40:32 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void				ft_putchar(char c)
{
	write(1, &c, 1);
}

static size_t		ft_strlen(char *str)
{
	size_t	nbr;

	nbr = 0;
	while (str[nbr])
		nbr = nbr + 1;
	return (nbr);
}

void				ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}
