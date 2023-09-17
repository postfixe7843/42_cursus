/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:59:04 by nlence-l          #+#    #+#             */
/*   Updated: 2023/07/22 16:09:19 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_data(t_data *data, int argc, char *argv[])
{
	data->t_start = find_time();
	data->num_philos = get_arg2(argv[1]);
	data->time_to_die = get_arg(argv[2]);
	data->time_to_eat = get_arg(argv[3]);
	data->time_to_sleep = get_arg(argv[4]);
	data->max_meals = -1;
	if (argc == 6)
	{
		data->max_meals = get_arg2(argv[5]);
		if (data->max_meals < 0)
			return (1);
	}
	data->game_over = 0;
	if (data->num_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (1);
	return (0);
}

int	init(t_data *data, int argc, char *argv[])
{
	if (init_data(data, argc, argv))
		return (1);
	sem_unlink("/print");
	sem_unlink("/fork");
	data->print = sem_open("/print", O_CREAT, 0600, 1);
	if (data->print == SEM_FAILED)
		return (1);
	data->fork = sem_open("/fork", O_CREAT, 0600, data->num_philos);
	if (data->fork == SEM_FAILED)
		return (1);
	return (0);
}

int	sim_start(t_data *data)
{
	if (pthread_create(&data->checker, NULL, &check_status, data))
		return (1);
	if (data->id % 2)
		usleep(100);
	while (1)
	{
		print(data, "is thinking");
		sem_wait(data->fork);
		print(data, "has taken a fork");
		sem_wait(data->fork);
		print(data, "has taken a fork");
		print(data, "is eating");
		ft_sleep(data->time_to_eat, data);
		data->t_last_meal = find_time();
		sem_post(data->fork);
		sem_post(data->fork);
		data->meals_count += 1;
		print(data, "is sleeping");
		ft_sleep(data->time_to_sleep, data);
	}
	if (pthread_join(data->checker, NULL))
		return (1);
}

void	*check_status(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (!data->game_over)
	{
		if (find_time() - data->t_last_meal > data->time_to_die)
		{
			sem_wait(data->print);
			printf("%lld %d %s\n", find_time() - data->t_start,
				data->id, "died");
			sem_post(data->print);
			data->game_over = 1;
		}
		if (data->max_meals != -1 && data->meals_count > data->max_meals)
			data->game_over = 1;
	}
	exit(0);
}

void	sim_stop(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < data->num_philos)
				kill(data->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(data->print);
	sem_close(data->fork);
}
