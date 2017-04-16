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

#include <stdlib.h>
#include "malloc.h"

#include <stdio.h>

int      main()
{
   size_t   nbr = 2;
   int      i = 1;

   while (i < 24)
   {
      malloc(nbr);
      nbr = nbr + nbr;
      i = i + 1;
   }
   show_alloc_mem();
   return (0);
}
