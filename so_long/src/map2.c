/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:15:41 by nlence-l          #+#    #+#             */
/*   Updated: 2023/06/29 18:34:39 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_display_wall(t_data *info, int *j, int *i)
{
	mlx_put_image_to_window(info->mlx, info->win,
		info->wall, (*j) * 32, (*i) * 32);
}

void	ft_display_player(t_data *info, int *j, int *i)
{
	mlx_put_image_to_window(info->mlx, info->win,
		info->player, (*j) * 32, (*i) * 32);
	info->x = *j;
	info->y = *i;
}

void	ft_display_collectible(t_data *info, int *j, int *i)
{
	mlx_put_image_to_window(info->mlx, info->win,
		info->collectible, (*j) * 32, (*i) * 32);
}

void	ft_display_exit(t_data *info, int *j, int *i)
{
	mlx_put_image_to_window(info->mlx, info->win,
		info->exit, (*j) * 32, (*i) * 32);
}

void	ft_display_empty(t_data *info, int *j, int *i)
{
	mlx_put_image_to_window(info->mlx, info->win,
		info->empty, (*j) * 32, (*i) * 32);
}
