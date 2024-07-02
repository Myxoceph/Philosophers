/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:19:32 by abakirca          #+#    #+#             */
/*   Updated: 2024/06/11 14:44:43 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdio.h>
#include <stdlib.h>

static int	zero_check(char *str_n)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str_n[i] == '0')
		i++;
	while (str_n[i + j])
		j++;
	if (j > 10)
		return (1);
	else
		return (0);
}

long	ft_atol(char *str)
{
	int		i;
	int		sign;
	long	tmp;

	if (zero_check(str) && printf("Max int error.\n"))
		exit (1);
	i = 0;
	sign = 1;
	tmp = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == 43 || str[i] == 45))
		if (str[i++] == 45)
			sign *= -1;
	while (str[i] >= 48 && str[i] <= 57)
		tmp = (tmp * 10) + (str[i++] - 48);
	if ((tmp * sign < -2147483648 || tmp * sign > 2147483647)
		&& printf("Max int error.\n"))
		exit(1);
	return (tmp * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	display(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->data->display);
	if (get_int(&philo->data->philodeadmtx, &philo->data->philo_dead) == 1)
	{
		pthread_mutex_unlock(&philo->data->display);
		return ;
	}
	time = get_time() - philo->philo_start;
	printf("%-6lld %d %s\n", time, philo->philo_index, msg);
	pthread_mutex_unlock(&philo->data->display);
}

void	wait_all_threads(t_data *data)
{
	while (!get_int(&data->all_th_ready_mutex, &data->all_th_ready))
		;
}
