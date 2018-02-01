/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <jcarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:11:33 by jcarra            #+#    #+#             */
/*   Updated: 2018/01/31 13:28:40 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <internal.h>

void				*malloc(size_t size)
{
	static pthread_mutex_t	mutex;
	static char				init = FALSE;
	void					*new;

	if (!init)
	{
		pthread_mutex_init(&mutex, NULL);
		init = TRUE;
	}
	pthread_mutex_lock(&mutex);
	new = ft_malloc(size);
	pthread_mutex_unlock(&mutex);
	return (new);
}

void				*realloc(void *ptr, size_t size)
{
	static pthread_mutex_t	mutex;
	static char				init = FALSE;
	void					*new;

	if (!init)
	{
		pthread_mutex_init(&mutex, NULL);
		init = TRUE;
	}
	pthread_mutex_lock(&mutex);
	new = ft_realloc(ptr, size);
	pthread_mutex_unlock(&mutex);
	return (new);
}

void				free(void *ptr)
{
	static pthread_mutex_t	mutex;
	static char				init = FALSE;

	if (!init)
	{
		pthread_mutex_init(&mutex, NULL);
		init = TRUE;
	}
	pthread_mutex_lock(&mutex);
	ft_free(ptr);
	pthread_mutex_unlock(&mutex);
}

void				show_alloc_mem(void)
{
	static pthread_mutex_t	mutex;
	static char				init = FALSE;

	if (!init)
	{
		pthread_mutex_init(&mutex, NULL);
		init = TRUE;
	}
	pthread_mutex_lock(&mutex);
	ft_show_alloc_mem();
	pthread_mutex_unlock(&mutex);
}
