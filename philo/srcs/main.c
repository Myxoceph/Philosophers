/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:19:22 by abakirca          #+#    #+#             */
/*   Updated: 2024/06/27 13:57:32 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((((long long)time.tv_sec) * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int wait_time)
{
	unsigned long long	time;

	time = get_time();
	while (get_time() - time < (unsigned long long)wait_time)
		usleep(100);
}

static int	control_data(t_data *data)
{
	if (data->philo_count < 1)
		return (1);
	if (data->philo_must_eat == 0)
		return (1);
	return (0);
}

static void	destroy(t_data *data, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->display);
	pthread_mutex_destroy(&data->philodeadmtx);
	pthread_mutex_destroy(&data->threadcheck);
	pthread_mutex_destroy(&data->philo_must_eat_mutex);
	pthread_mutex_destroy(&data->all_th_ready_mutex);
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].philo_last_eat_mutex);
		philos[i].left_fork = NULL;
		philos[i].right_fork = NULL;
	}
	free(forks);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (arg_control(argc, argv) || init_data(&data, argv))
		return (1);
	if (control_data(&data))
		return (1);
	if (!init_extra_mutexes(&data))
		return (1);
	forks = init_forks(&data);
	if (!forks)
		return (1);
	philo = init_philo(&data, forks);
	if (!philo)
		return (1);
	if (start_simulation(&data, philo))
		destroy(&data, forks, philo);
}
