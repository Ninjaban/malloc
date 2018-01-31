/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 09:13:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/25 15:41:46 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "internal.h"

static void		ft_putnbr_hexa_single(size_t c)
{
	if (c <= 9)
		ft_putchar(48 + c);
	else
		ft_putchar(97 + c - 10);
}

static int		ft_putnbr_hexa(size_t nbr)
{
	size_t	max;
	size_t	value;
	int		n;

	n = 0;
	while (nbr >= 16)
	{
		max = 16;
		while (max * 16 < nbr)
			max *= 16;
		value = nbr / max;
		nbr -= value * max;
		ft_putnbr_hexa_single(value);
		n++;
	}
	ft_putnbr_hexa_single(nbr);
	n++;
	return (n);
}

void			ft_print_address(size_t addr)
{
	int size;

	ft_putstr("0x");
	size = ft_putnbr_hexa(addr);
	while (size++ < 9)
		ft_putchar('0');
}

void			ft_putnbr_sizet(size_t nbr)
{
	if (nbr >= 10)
	{
		ft_putnbr_sizet(nbr / 10);
		ft_putnbr_sizet(nbr % 10);
	}
	else
		ft_putchar(nbr + 48);
}
