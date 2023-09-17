/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:58:47 by nlence-l          #+#    #+#             */
/*   Updated: 2023/07/20 16:00:47 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	pthread_t		checker;
	int				id;
	int				num_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		t_start;
	long long		t_last_meal;
	int				game_over;
	int				meals_count;
	int				max_meals;
	sem_t			*print;
	sem_t			*fork;
	pid_t			pid[150];
}t_data;

int			init_data(t_data *data, int argc, char *argv[]);
int			init(t_data *data, int argc, char *argv[]);
int			sim_start(t_data *data);
void		sim_stop(t_data *data);
void		*check_status(void *args);
void		print(t_data *data, char *str);
long long	find_time(void);
long long	get_arg(char *str);
int			get_arg2(char *str);
void		ft_sleep(long long time, t_data *data);

#endif
