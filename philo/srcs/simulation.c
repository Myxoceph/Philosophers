/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:19:28 by abakirca          #+#    #+#             */
/*   Updated: 2024/06/26 17:02:50 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdio.h>

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
	display(philo, FORK);
	display(philo, EATING);
	if (get_int(&philo->data->all_th_ready_mutex, &philo->data->philo_must_eat))
		set_int(&philo->data->philo_must_eat_mutex,
			&philo->philo_loop, philo->philo_loop - 1);
	pthread_mutex_lock(&philo->philo_last_eat_mutex);
	philo->philo_last_eat = get_time();
	pthread_mutex_unlock(&philo->philo_last_eat_mutex);
	ft_usleep(philo->data->philo_eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	display(philo, SLEEPING);
	ft_usleep(philo->data->philo_sleep_time);
	display(philo, THINKING);
}

static void	observer(t_philo *philo, int i)
{
	if (philo->data->threadcount != philo->data->philo_count - 1)
		return ;
	while (get_int(&philo->data->philodeadmtx, &philo->data->philo_dead) != 1)
	{
		if (all_fed(philo))
		{
			set_int(&philo->data->philodeadmtx, &philo->data->philo_dead, 1);
			return ;
		}
		if ((get_time() - get_long(&philo[i].philo_last_eat_mutex,
					&philo[i].philo_last_eat))
			>= get_int(&philo->philo_last_eat_mutex,
				&philo[i].data->philo_live_time))
		{
			display(philo + i, DEAD);
			set_int(&philo->data->philodeadmtx,
				&philo->data->philo_dead, 1);
			break ;
		}
		i++;
		if (i == philo->data->philo_count)
			i = 0;
	}
}

static void	one_philo(t_philo *philo)
{
	display(philo, FORK);
	ft_usleep(philo->data->philo_live_time);
	display(philo, DEAD);
	return ;
}

static void	*philo_routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	wait_all_threads(philo->data);
	if (philo->data->threadcount != philo->data->philo_count - 1)
		return (NULL);
	set_long(&philo->philo_last_eat_mutex, &philo->philo_last_eat, get_time());
	if (philo->data->philo_count == 1)
		return (one_philo(philo), NULL);
	if (philo->philo_index % 2 == 0)
	{
		ft_usleep(philo->data->philo_eat_time);
		set_long(&philo->philo_last_eat_mutex,
			&philo->philo_last_eat, get_time());
	}
	while (!get_int(&philo->data->philodeadmtx, &philo->data->philo_dead))
	{
		if (philo->philo_loop == 0)
			break ;
		eat(philo);
	}
	return (NULL);
}

int	start_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	data->threadcount = -1;
	data->all_th_ready = 0;
	while (++i < data->philo_count)
	{
		philo[i].philo_start = get_time();
		if (pthread_create(&philo[i].philo_thread, NULL, philo_routine,
				&philo[i]) && printf("%s\n", THREAD_CREATE_ERR))
			break ;
		data->threadcount++;
	}
	set_int(&data->all_th_ready_mutex, &data->all_th_ready, 1);
	observer(philo, 0);
	i = -1;
	while (++i < data->threadcount + 1)
		if (pthread_join(philo[i].philo_thread, NULL) && printf("%s\n",
				THREAD_JOIN_ERR))
			return (1);
	return (1);
}
