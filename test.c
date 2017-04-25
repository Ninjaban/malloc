/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 16:06:41 by mrajaona          #+#    #+#             */
/*   Updated: 2017/04/25 16:27:46 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"

int	main(void)
{
	size_t 	i;
	char	*addr;

	i = 1;
	addr = NULL;
	while (i < 999999999)
	{
		if ((addr = realloc(addr, i)))
			printf("%p\t%zu\n", addr, i);
		i *= 5;
	}
	if (addr)
		free(addr);
	printf("DONE\n");
}
