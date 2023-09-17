/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:16:28 by nlence-l          #+#    #+#             */
/*   Updated: 2023/06/29 18:44:38 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	ft_exit(t_data *info)
{
	(void) *info;
	exit(EXIT_SUCCESS);
}

int	ft_press_key(int keycode, t_data *info)
{
	if (keycode == W)
		ft_move_w(info);
	else if (keycode == A)
		ft_move_a(info);
	else if (keycode == S)
		ft_move_s(info);
	else if (keycode == D)
		ft_move_d(info);
	else if (keycode == ESC)
		ft_exit(info);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	info;
	t_path	p;

	if (ac == 2)
	{
		info.mlx = mlx_init();
		ft_init(&info, av[1]);
		ft_map_height(&info);
		ft_read_map(&info);
		if (ft_check(&info) == 1)
			ft_exit(&info);
		ft_init_path(&info, &p);
		if (ft_path(&info, &p) == 1)
			ft_exit(&info);
		info.win = mlx_new_window(info.mlx, info.width * 32,
				info.height * 32, "so_long");
		ft_display_map(&info);
		mlx_hook(info.win, 17, 0, ft_exit, &info);
		mlx_hook(info.win, 02, 0, ft_press_key, &info);
		mlx_loop_hook(info.mlx, ft_refresh, &info);
		mlx_loop(info.mlx);
	}
	return (0);
}
