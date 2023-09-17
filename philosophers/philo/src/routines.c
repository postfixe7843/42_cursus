/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:10:21 by nlence-l          #+#    #+#             */
/*   Updated: 2023/07/20 15:34:49 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->data->game_over)
	{
		print(philo, "is thinking");
		pthread_mutex_lock(&philo->data->forks[philo->lf]);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->rf]);
		print(philo, "has taken a fork");
		print(philo, "is eating");
		ft_sleep(philo->data->time_to_eat, philo->data);
		philo->t_last_meal = find_time();
		pthread_mutex_unlock(&philo->data->forks[philo->lf]);
		pthread_mutex_unlock(&philo->data->forks[philo->rf]);
		if (!philo->data->game_over)
			philo->num_meals++;
		print(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep, philo->data);
	}
	return (NULL);
}

void	*check_status(void *args)
{
	t_philo	*philos;
	int		i;
	int		all_eat;

	philos = (t_philo *)args;
	while (!philos->data->game_over)
	{
		i = -1;
		all_eat = 0;
		while (++i < philos->data->num_philos)
		{
			if (find_time() - (philos + i)->t_last_meal
				> philos->data->time_to_die)
			{
				print(philos + i, "died");
				philos->data->game_over = 1;
			}
			if (philos->data->max_meals != -1 && (philos + i)->num_meals
				>= philos->data->max_meals)
				all_eat++;
		}
		if (all_eat >= philos->data->num_philos)
			philos->data->game_over = 1;
	}
	return (NULL);
}
