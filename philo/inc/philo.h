/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:53:21 by abakirca          #+#    #+#             */
/*   Updated: 2024/06/26 16:32:24 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define INVALID_ARGS_ERR "Invalid arguments"
# define THREAD_CREATE_ERR "Failed to create a thread"
# define THREAD_JOIN_ERR "Failed to join a thread"
# define MALLOC_ERR "malloc() failed to allocate memory"
# define MUTEX_INIT_ERR "Failed to initialize mutex"

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"

typedef struct s_data
{
	int				philo_count;
	int				philo_live_time;
	int				philo_eat_time;
	int				philo_sleep_time;
	int				philo_must_eat;
	int				philo_dead;
	int				threadcount;
	int				all_th_ready;
	pthread_mutex_t	all_th_ready_mutex;
	pthread_mutex_t	philo_must_eat_mutex;
	pthread_mutex_t	threadcheck;
	pthread_mutex_t	philodeadmtx;
	pthread_mutex_t	display;
}					t_data;

typedef struct s_philo
{
	int				philo_index;
	int				philo_loop;
	long long		philo_start;
	long long		philo_last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_last_eat_mutex;
	pthread_t		philo_thread;
	t_data			*data;
}					t_philo;

int					init_data(t_data *data, char **argv);
int					arg_control(int argc, char **argv);
pthread_mutex_t		*init_forks(t_data *data);
t_philo				*init_philo(t_data *data, pthread_mutex_t *forks);
int					start_simulation(t_data *data, t_philo *philo);
void				display(t_philo *philo, char *msg);
void				ft_usleep(int wait_time);
long long			get_time(void);
int					ft_isdigit(int c);
long				ft_atol(char *str);
void				set_int(pthread_mutex_t	*mutex, int *dst, int value);
int					get_int(pthread_mutex_t *mutex, int *value);
void				set_long(pthread_mutex_t *mutex, long long *dst,
						long long value);
long long			get_long(pthread_mutex_t *mutex, long long *value);
void				init_philo_err(t_philo *philo, pthread_mutex_t *forks,
						t_data *data, int i);
void				init_forks_err(t_data *data, pthread_mutex_t *forks, int i);
void				wait_all_threads(t_data *data);
void				destroy_extra_mutexes(t_data *data, int flag);
int					init_extra_mutexes(t_data *data);
int					all_fed(t_philo *philo);

#endif
