/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:19:44 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/18 17:30:01 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include "../libft/inc/libft.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[0] == '-')
		sign = -1;
	if (str[i] >= '0' && str[i] <= '9')
	{
		while (str[i] <= '9' && str[i] >= '0')
		{
			res = res * 10 + str[i] - '0';
			i++;
		}
	}
	return (res * sign);
}

void	ft_sender(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c & (0x01 << i)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(400);
		i++;
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	i = 0;
	if (ac == 3)
	{	
		pid = ft_atoi(av[1]);
		while (av[2][i] != '\0')
		{
			ft_sender(pid, av[2][i]);
			i++;
		}
		ft_sender(pid, '\0');
	}
	else
	{
		ft_printf("usage: ./client <server's pid> <string>\n");
		return (1);
	}
	return (0);
}
