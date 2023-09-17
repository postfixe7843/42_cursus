/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:33:01 by nlence-l          #+#    #+#             */
/*   Updated: 2023/06/30 18:37:36 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_sub1(t_data *info, int ***matrix, t_path *p)
{
	if (info->map[p->i - 1][p->j] == 'C')
		p->coll--;
	if (info->map[p->i - 1][p->j] == 'E')
	{
		p->exit_reachable = 1;
		if (p->coll == 0)
		{
			(*matrix)[p->i - 1][p->j] = p->k + 1;
			return ;
		}
		else
			return ;
	}
	(*matrix)[p->i - 1][p->j] = p->k + 1;
}

void	ft_sub2(t_data *info, int ***matrix, t_path *p)
{
	if (info->map[p->i + 1][p->j] == 'C')
		p->coll--;
	if (info->map[p->i + 1][p->j] == 'E')
	{
		p->exit_reachable = 1;
		if (p->coll == 0)
		{
			(*matrix)[p->i + 1][p->j] = p->k + 1;
			return ;
		}
		else
			return ;
	}
	(*matrix)[p->i + 1][p->j] = p->k + 1;
}

void	ft_sub3(t_data *info, int ***matrix, t_path *p)
{
	if (info->map[p->i][p->j - 1] == 'C')
		p->coll--;
	if (info->map[p->i][p->j - 1] == 'E')
	{
		p->exit_reachable = 1;
		if (p->coll == 0)
		{
			(*matrix)[p->i][p->j - 1] = p->k + 1;
			return ;
		}
		else
			return ;
	}
	(*matrix)[p->i][p->j - 1] = p->k + 1;
}

void	ft_sub4(t_data *info, int ***matrix, t_path *p)
{
	if (info->map[p->i][p->j + 1] == 'C')
		p->coll--;
	if (info->map[p->i][p->j + 1] == 'E')
	{
		p->exit_reachable = 1;
		if (p->coll == 0)
		{
			(*matrix)[p->i][p->j + 1] = p->k + 1;
			return ;
		}
		else
			return ;
	}
	(*matrix)[p->i][p->j + 1] = p->k + 1;
}

void	ft_sub_step(t_data *info, int ***matrix, t_path *p)
{
	if ((*matrix)[p->i - 1][p->j] == 0 && (info->map[p->i - 1][p->j] == '0' ||
		info->map[p->i - 1][p->j] == 'C' || info->map[p->i - 1][p->j] == 'E'))
		ft_sub1(info, matrix, p);
	if ((*matrix)[p->i + 1][p->j] == 0 && (info->map[p->i + 1][p->j] == '0' ||
		info->map[p->i + 1][p->j] == 'C' || info->map[p->i + 1][p->j] == 'E'))
		ft_sub2(info, matrix, p);
	if ((*matrix)[p->i][p->j - 1] == 0 && (info->map[p->i][p->j - 1] == '0' ||
		info->map[p->i][p->j - 1] == 'C' || info->map[p->i][p->j - 1] == 'E'))
		ft_sub3(info, matrix, p);
	if ((*matrix)[p->i][p->j + 1] == 0 && (info->map[p->i][p->j + 1] == '0' ||
		info->map[p->i][p->j + 1] == 'C' || info->map[p->i][p->j + 1] == 'E'))
		ft_sub4(info, matrix, p);
}
