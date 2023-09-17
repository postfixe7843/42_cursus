/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:59:16 by nlence-l          #+#    #+#             */
/*   Updated: 2023/07/20 16:04:35 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	if (argc < 5 || argc > 6)
		return (1);
	if (init(&data, argc, argv))
		return (1);
	i = -1;
	while (++i < data.num_philos)
	{
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			return (1);
		if (data.pid[i] == 0)
		{
			data.id = i + 1;
			data.t_last_meal = find_time();
			sim_start(&data);
		}
		usleep(100);
	}
	sim_stop(&data);
	return (0);
}
