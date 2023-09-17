/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:10:37 by nlence-l          #+#    #+#             */
/*   Updated: 2023/07/20 15:28:47 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->game_over)
		printf("%lld %d %s\n", find_time() - philo->data->t_start,
			philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

int	start_threads(t_data *data)
{
	int	i;

	i = -1;
	data->t_start = find_time();
	while (++i < data->num_philos)
	{
		data->philos[i].t_last_meal = find_time();
		if (pthread_create(&data->philos[i].thread_id, NULL,
				&routine, &(data->philos[i])))
			return (1);
		pthread_detach(data->philos[i].thread_id);
		usleep(100);
	}
	if (pthread_create(&data->checker, NULL, &check_status, data->philos))
		return (1);
	if (pthread_join(data->checker, NULL))
		return (1);
	usleep(10000);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print);
	free(data->philos);
	free(data->forks);
	return (0);
}
