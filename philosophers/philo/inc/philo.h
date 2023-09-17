/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:09:32 by nlence-l          #+#    #+#             */
/*   Updated: 2023/07/20 15:12:20 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		t_start;
	int				game_over;
	int				meals_count;
	int				max_meals;
	t_philo			*philos;
	pthread_t		checker;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}t_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread_id;
	int				id;
	int				num_meals;
	long long		t_last_meal;
	int				rf;
	int				lf;
}t_philo;

void		print(t_philo *philo, char *str);
int			start_threads(t_data *data);
void		*routine(void *args);
void		*check_status(void *args);
int			init_data(t_data *data, int ac, char **av);
int			init_mutex(t_data *data);
int			init_philo(t_data *data);
int			init(t_data *data, int ac, char **av);
long long	find_time(void);
long long	get_arg(char *str);
int			get_arg2(char *str);
void		ft_sleep(long long time, t_data *data);

#endif
