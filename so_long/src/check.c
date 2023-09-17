/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:14:49 by nlence-l          #+#    #+#             */
/*   Updated: 2023/06/29 18:29:01 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	ft_check_walls1(t_data *info)
{
	int	j;

	j = 0;
	while (info->map[0][j])
	{
		if (info->map[0][j] != '1')
		{
			write(2, "Error.\n", 7);
			write(2, "The map isn't surrounded by walls!\n", 35);
			return (1);
		}
		j++;
	}
	j = 0;
	while (info->map[info->height - 1][j])
	{
		if (info->map[info->height - 1][j] != '1')
		{
			write(2, "Error.\n", 7);
			write(2, "The map isn't surrounded by walls!\n", 35);
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_check_walls2(t_data *info)
{
	int	i;

	i = 0;
	while (info->map[i])
	{
		if (info->map[i][0] != '1' ||
				info->map[i][ft_strlen(info->map[i]) - 1] != '1')
		{
			write(2, "Error.\n", 7);
			write(2, "The map isn't surrounded by walls!\n", 35);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_shape(t_data *info)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(info->map[0]);
	while (info->map[i])
	{
		if ((int)ft_strlen(info->map[i]) == len)
			i++;
		else
		{
			write(2, "Error.\n", 7);
			write(2, "The map isn't rectangular!\n", 27);
			return (1);
		}
	}
	return (0);
}

int	ft_check_elements(t_data *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->map[i])
	{
		while (info->map[i][j])
		{
			if (info->map[i][j] != '1' && info->map[i][j] != '0'
					&& info->map[i][j] != 'P'
					&& info->map[i][j] != 'C' && info->map[i][j] != 'E')
			{
				write(2, "Error.\n", 7);
				write(2, "Forbidden element detected!\n", 28);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	ft_check_valid_pce(t_data *info)
{
	if (info->collectibles < 1)
	{
		write(2, "Error.\n", 7);
		write(2, "No collectibles detected!\n", 26);
		return (1);
	}
	else if (info->check_e != 1)
	{
		write(2, "Error.\n", 7);
		write(2, "More than one exit detected!\n", 29);
		return (1);
	}
	else if (info->check_p > 1)
	{
		write(2, "Error.\n", 7);
		write(2, "More than one player detected!\n", 31);
		return (1);
	}
	return (0);
}
