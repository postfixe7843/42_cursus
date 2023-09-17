/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:09:54 by nlence-l          #+#    #+#             */
/*   Updated: 2023/07/20 15:13:38 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->num_philos = get_arg2(av[1]);
	if (data->num_philos > 250)
		return (1);
	data->time_to_die = get_arg(av[2]);
	data->time_to_eat = get_arg(av[3]);
	data->time_to_sleep = get_arg(av[4]);
	data->max_meals = -1;
	if (ac == 6)
	{
		data->max_meals = get_arg2(av[5]);
		if (data->max_meals < 0)
			return (1);
	}
	if (data->num_philos < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].num_meals = 0;
		data->philos[i].id = i + 1;
		data->philos[i].lf = i;
		data->philos[i].rf = (i + 1) % data->num_philos;
		data->philos[i].data = data;
	}
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	if (init_data(data, ac, av))
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		free(data->philos);
		return (1);
	}
	if (init_mutex(data))
	{
		free(data->philos);
		free(data->forks);
		return (1);
	}
	if (init_philo(data))
	{
		free(data->philos);
		free(data->forks);
		return (1);
	}
	return (0);
}
