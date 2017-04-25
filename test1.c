/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 15:21:16 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/25 15:39:19 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"

int	main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	return (0);
}

/*
int	main(void)
{
   int	i;
   char	*addr;

   i = 0;
   while (i < 1024)
   {
      addr = malloc(1);
      addr[0] = 42;
      i++;
   }
	show_alloc_mem();
   return (0);
}
*/
