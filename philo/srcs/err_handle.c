/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:24:58 by abakirca          #+#    #+#             */
/*   Updated: 2024/06/27 14:01:38 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdlib.h>
#include <stdio.h>

void	destroy_extra_mutexes(t_data *data, int flag)
{
	if (flag < 1)
		pthread_mutex_destroy(&data->display);
	if (flag < 2)
		pthread_mutex_destroy(&data->philodeadmtx);
	if (flag < 3)
		pthread_mutex_destroy(&data->threadcheck);
	if (flag < 4)
		pthread_mutex_destroy(&data->philo_must_eat_mutex);
	if (flag < 5)
		pthread_mutex_destroy(&data->all_th_ready_mutex);
}

void	init_forks_err(t_data *data, pthread_mutex_t *forks, int i)
{
	while (--i > -1)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
	destroy_extra_mutexes(data, 4);
	return ;
}

void	init_philo_err(t_philo *philo, pthread_mutex_t *forks,
				t_data *data, int i)
{
	while (--i > -1)
		pthread_mutex_destroy(&philo[i].philo_last_eat_mutex);
	init_forks_err(data, forks, data->philo_count);
	free(philo);
	return ;
}

int	init_extra_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->display, NULL) && printf("%s\n",
			MUTEX_INIT_ERR))
		return (0);
	if (pthread_mutex_init(&data->philodeadmtx, NULL) && printf("%s\n",
			MUTEX_INIT_ERR))
		return (destroy_extra_mutexes(data, 0), 0);
	if (pthread_mutex_init(&data->threadcheck, NULL) && printf("%s\n",
			MUTEX_INIT_ERR))
		return (destroy_extra_mutexes(data, 1), 0);
	if (pthread_mutex_init(&data->philo_must_eat_mutex, NULL) && printf("%s\n",
			MUTEX_INIT_ERR))
		return (destroy_extra_mutexes(data, 2), 0);
	if (pthread_mutex_init(&data->all_th_ready_mutex, NULL) && printf("%s\n",
			MUTEX_INIT_ERR))
		return (destroy_extra_mutexes(data, 3), 0);
	return (1);
}
