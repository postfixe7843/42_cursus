/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:59:28 by nlence-l          #+#    #+#             */
/*   Updated: 2023/07/20 16:05:18 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	print(t_data *data, char *str)
{
	sem_wait(data->print);
	if (!data->game_over)
		printf("%lld %d %s\n", find_time() - data->t_start, data->id, str);
	sem_post(data->print);
}

long long	find_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

long long	get_arg(char *str)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		res = 10 * res + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	get_arg2(char *str)
{
	int			i;
	int			res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		res = 10 * res + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

void	ft_sleep(long long time, t_data *data)
{
	long long	start;

	start = find_time();
	while (!data->game_over)
	{
		if (find_time() - start >= time)
			break ;
		usleep(100);
	}
}
