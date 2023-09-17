/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:21:25 by nlence-l          #+#    #+#             */
/*   Updated: 2023/06/30 18:40:22 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define BUFFER_SIZE    5
# define ESC            53
# define W              13
# define A              0
# define S              1
# define D              2
# define PLAYER         "./sprites/player.xpm"
# define COLLECTIBLE    "./sprites/collectible.xpm"
# define EXIT           "./sprites/exit.xpm"
# define WALL           "./sprites/wall.xpm"
# define EMPTY          "./sprites/empty.xpm"

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/inc/libft.h"

typedef struct s_data
{
	int		width;
	int		height;
	int		x;
	int		y;
	int		collectibles;
	void	*mlx;
	void	*win;
	char	*name;
	char	**map;
	int		check_p;
	int		check_e;
	int		game_over;
	int		moves;
	void	*player;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*empty;
}				t_data;

typedef struct s_path
{
	int	i;
	int	j;
	int	k;
	int	coll;
	int	x_end;
	int	y_end;
	int	exit_reachable;
}	t_path;

void	ft_init_sprites(t_data *info);
void	ft_init(t_data *info, char *name);
void	ft_display_map(t_data *info);
int		ft_refresh(t_data *info);
void	ft_finish(t_data *info);
void	ft_display_wall(t_data *info, int *j, int *i);
void	ft_display_player(t_data *info, int *j, int *i);
void	ft_display_collectible(t_data *info, int *j, int *i);
void	ft_display_exit(t_data *info, int *j, int *i);
void	ft_display_empty(t_data *info, int *j, int *i);
void	ft_move_d(t_data *info);
void	ft_move_w(t_data *info);
void	ft_move_a(t_data *info);
void	ft_move_s(t_data *info);
int		ft_exit(t_data *info);
int		ft_press_key(int keycode, t_data *info);
void	ft_map_height(t_data *info);
void	ft_read_map(t_data *info);
int		ft_check(t_data *info);
int		ft_check_walls1(t_data *info);
int		ft_check_walls2(t_data *info);
int		ft_check_shape(t_data *info);
int		ft_check_elements(t_data *info);
void	ft_check_nb_pce(t_data *info);
int		ft_check_valid_pce(t_data *info);
int		ft_path(t_data *info, t_path *p);
void	ft_find_start_end(t_data *info, int ***matrix, t_path *p);
int		**ft_generate_matrix(t_data *info);
void	ft_sub_step(t_data *info, int ***matrix, t_path *p);
void	ft_step(t_data *info, int ***matrix, t_path *p);
void	ft_init_path(t_data *info, t_path *p);
void	ft_sub1(t_data *info, int ***matrix, t_path *p);
void	ft_sub2(t_data *info, int ***matrix, t_path *p);
void	ft_sub3(t_data *info, int ***matrix, t_path *p);
void	ft_sub4(t_data *info, int ***matrix, t_path *p);

#endif
