/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:15:58 by nlence-l          #+#    #+#             */
/*   Updated: 2023/06/29 18:38:49 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_move_d(t_data *info)
{
	if (info->map[info->y][info->x + 1] == '1')
		return ;
	if (info->map[info->y][info->x + 1] == 'C')
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y][info->x + 1] = 'P';
		info->collectibles--;
	}
	else if (info->map[info->y][info->x + 1] == '0')
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y][info->x + 1] = 'P';
	}
	else if (info->map[info->y][info->x + 1] ==
		'E' && info->collectibles == 0)
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y][info->x - 1] = 'P';
		info->game_over = 1;
	}
	else if (info->map[info->y][info->x + 1] == 'E' && info->collectibles > 0)
		return ;
	info->x++;
	info->moves++;
	ft_printf("Moves: %d\n", info->moves);
}

void	ft_move_w(t_data *info)
{
	if (info->map[info->y - 1][info->x] == '1')
		return ;
	if (info->map[info->y - 1][info->x] == 'C')
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y - 1][info->x] = 'P';
		info->collectibles--;
	}
	else if (info->map[info->y - 1][info->x] == '0')
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y - 1][info->x] = 'P';
	}
	else if (info->map[info->y - 1][info->x] ==
		'E' && info->collectibles == 0)
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y][info->x - 1] = 'P';
		info->game_over = 1;
	}
	else if (info->map[info->y - 1][info->x] == 'E' && info->collectibles > 0)
		return ;
	info->y--;
	info->moves++;
	ft_printf("Moves: %d\n", info->moves);
}

void	ft_move_a(t_data *info)
{
	if (info->map[info->y][info->x - 1] == '1')
		return ;
	if (info->map[info->y][info->x - 1] == 'C')
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y][info->x - 1] = 'P';
		info->collectibles--;
	}
	else if (info->map[info->y][info->x - 1] == '0')
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y][info->x - 1] = 'P';
	}
	else if (info->map[info->y][info->x - 1] ==
		'E' && info->collectibles == 0)
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y][info->x - 1] = 'P';
		info->game_over = 1;
	}
	else if (info->map[info->y][info->x - 1] == 'E' && info->collectibles > 0)
		return ;
	info->x--;
	info->moves++;
	ft_printf("Moves: %d\n", info->moves);
}

void	ft_move_s(t_data *info)
{
	if (info->map[info->y + 1][info->x] == '1')
		return ;
	if (info->map[info->y + 1][info->x] == 'C')
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y + 1][info->x] = 'P';
		info->collectibles--;
	}
	else if (info->map[info->y + 1][info->x] == '0')
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y + 1][info->x] = 'P';
	}
	else if (info->map[info->y + 1][info->x] ==
		'E' && info->collectibles == 0)
	{
		info->map[info->y][info->x] = '0';
		info->map[info->y][info->x - 1] = 'P';
		info->game_over = 1;
	}
	else if (info->map[info->y + 1][info->x] == 'E' && info->collectibles > 0)
		return ;
	info->y++;
	info->moves++;
	ft_printf("Moves: %d\n", info->moves);
}
