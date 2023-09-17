/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:27:47 by nlence-l          #+#    #+#             */
/*   Updated: 2023/06/30 18:38:12 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	ft_check(t_data *info)
{
	ft_check_nb_pce(info);
	if (ft_check_walls1(info) == 1)
		return (1);
	if (ft_check_walls2(info) == 1)
		return (1);
	if (ft_check_shape(info) == 1)
		return (1);
	if (ft_check_elements(info) == 1)
		return (1);
	if (ft_check_valid_pce(info) == 1)
		return (1);
	return (0);
}

void	ft_check_nb_pce(t_data *info)
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
				info->check_p += 1;
			else if (info->map[i][j] == 'C')
				info->collectibles += 1;
			else if (info->map[i][j] == 'E')
				info->check_e += 1;
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_init_path(t_data *info, t_path *p)
{
	p->coll = info->collectibles;
	p->exit_reachable = 0;
	p->k = 1;
	p->i = 0;
	p->j = 0;
}
