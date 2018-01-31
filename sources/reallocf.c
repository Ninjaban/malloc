/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:49:19 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/31 12:52:17 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

void		*reallocf(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!(new_ptr = realloc(ptr, size)))
	{
		free(ptr);
		return (NULL);
	}
	return (new_ptr);
}
