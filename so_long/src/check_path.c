/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:29:53 by nlence-l          #+#    #+#             */
/*   Updated: 2023/06/30 18:32:27 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	**ft_generate_matrix(t_data *info)
{
	int	**matrix;
	int	i;
	int	j;

	i = 0;
	j = 0;
	matrix = (int **)malloc(sizeof(int *) * info->height);
	while (i < info->height)
	{
		matrix[i] = (int *)malloc(sizeof(int) * info->width);
		while (j < info->width)
		{
			matrix[i][j] = 0;
			j++;
		}
		j = 0;
		i++;
	}
	return (matrix);
}

void	ft_find_start_end(t_data *info, int ***matrix, t_path *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->map[i])
	{
		while (info->map[i][j])
		{
			if (info->map[i][j] == 'P')
				(*matrix)[i][j] = 1;
			else if (info->map[i][j] == 'E')
			{
				p->x_end = j;
				p->y_end = i;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_step(t_data *info, int ***matrix, t_path *p)
{
	p->i = 0;
	p->j = 0;
	while (p->i < info->height)
	{
		while (p->j < info->width)
		{
			if ((*matrix)[p->i][p->j] == p->k)
				ft_sub_step(info, matrix, p);
			p->j++;
		}
		p->j = 0;
		p->i++;
	}
	p->k++;
}

void	ft_free_matrix(int ***matrix, t_data *info)
{
	int	i;

	i = 0;
	while (i < info->height)
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

int	ft_path(t_data *info, t_path *p)
{
	int	**matrix;
	int	max_try;

	matrix = ft_generate_matrix(info);
	max_try = info->width * info->height * 2;
	ft_find_start_end(info, &matrix, p);
	while (matrix[p->y_end][p->x_end] == 0 && max_try > 0)
	{
		ft_step(info, &matrix, p);
		max_try--;
	}
	ft_free_matrix(&matrix, info);
	if (p->exit_reachable == 1 && p->coll == 0)
		return (0);
	write(2, "Error.\n", 7);
	write(2, "The map isn't playable!\n", 24);
	return (1);
}
