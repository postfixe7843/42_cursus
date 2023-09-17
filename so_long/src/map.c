/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:15:22 by nlence-l          #+#    #+#             */
/*   Updated: 2023/06/30 18:38:30 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_init_sprites(t_data *info)
{
	int	img_height;
	int	img_width;

	info->player = mlx_xpm_file_to_image(info->mlx, PLAYER,
			&img_width, &img_height);
	if (info->player == NULL)
		ft_exit(info);
	info->wall = mlx_xpm_file_to_image(info->mlx, WALL,
			&img_width, &img_height);
	if (info->wall == NULL)
		ft_exit(info);
	info->collectible = mlx_xpm_file_to_image(info->mlx, COLLECTIBLE,
			&img_width, &img_height);
	if (info->collectible == NULL)
		ft_exit(info);
	info->exit = mlx_xpm_file_to_image(info->mlx, EXIT,
			&img_width, &img_height);
	if (info->exit == NULL)
		ft_exit(info);
	info->empty = mlx_xpm_file_to_image(info->mlx, EMPTY,
			&img_width, &img_height);
	if (info->empty == NULL)
		ft_exit(info);
}

void	ft_init(t_data *info, char *name)
{
	info->check_e = 0;
	info->check_p = 0;
	info->height = 0;
	info->width = 0;
	info->game_over = 0;
	info->collectibles = 0;
	info->moves = 0;
	info->x = 0;
	info->y = 0;
	info->player = 0;
	info->name = name;
	ft_init_sprites(info);
}

void	ft_display_map(t_data *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->map[i])
	{
		while (info->map[i][j])
		{
			if (info->map[i][j] == '1')
				ft_display_wall(info, &j, &i);
			else if (info->map[i][j] == '0')
				ft_display_empty(info, &j, &i);
			else if (info->map[i][j] == 'P')
				ft_display_player(info, &j, &i);
			else if (info->map[i][j] == 'E')
				ft_display_exit(info, &j, &i);
			else if (info->map[i][j] == 'C')
				ft_display_collectible(info, &j, &i);
			j++;
		}
		i++;
		j = 0;
	}
}

int	ft_refresh(t_data *info)
{
	mlx_clear_window(info->mlx, info->win);
	ft_display_map(info);
	if (info->collectibles == 0 && info->game_over == 1)
		ft_finish(info);
	return (0);
}

void	ft_finish(t_data *info)
{
	mlx_clear_window(info->mlx, info->win);
	ft_exit(info);
}
