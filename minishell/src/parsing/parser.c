/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:22:05 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/18 17:04:08 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	**parser(t_prompt *p)
{
	t_command	**res;
	int			cmds_nbr;
	int			i;
	int			index;

	cmds_nbr = get_cmds_nbr(p->tokens);
	i = 0;
	index = 0;
	res = (t_command **)malloc(sizeof(t_command *) * (cmds_nbr + 1));
	if (!res)
		return (NULL);
	while (i < cmds_nbr)
	{
		res[i] = create_cmd(p, &index);
		if (!res[i])
			break ;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	copy_into_filename(char *filename, char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		filename[i] = value[i];
		i++;
	}
	filename[i] = '\0';
}
