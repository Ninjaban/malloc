/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 15:21:16 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/14 15:21:57 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"

int      main()
{
	int   i;
	char  *addr;

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

/*
int      main()
{
   int   i;
   char  *addr;

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