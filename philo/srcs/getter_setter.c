/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:58:11 by abakirca          #+#    #+#             */
/*   Updated: 2024/06/11 14:46:01 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_int(pthread_mutex_t	*mutex, int *dst, int value)
{
	pthread_mutex_lock(mutex);
	*dst = value;
	pthread_mutex_unlock(mutex);
}

int	get_int(pthread_mutex_t *mutex, int *value)
{
	int	retrieved;

	pthread_mutex_lock(mutex);
	retrieved = *value;
	pthread_mutex_unlock(mutex);
	return (retrieved);
}

void	set_long(pthread_mutex_t *mutex, long long *dst, long long value)
{
	pthread_mutex_lock(mutex);
	*dst = value;
	pthread_mutex_unlock(mutex);
}

long long	get_long(pthread_mutex_t *mutex, long long *value)
{
	long long	retrieve;

	pthread_mutex_lock(mutex);
	retrieve = *value;
	pthread_mutex_unlock(mutex);
	return (retrieve);
}
