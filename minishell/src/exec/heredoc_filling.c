/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_filling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:43:04 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 16:44:59 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_line(char *line, char *delim)
{
	if (line == NULL)
		return (0);
	if (ft_strcmp(line, delim) == 0 || g_status == 99)
		return (1);
	return (0);
}

void	end_line(char *line, int fd)
{
	char	*tmp_line;

	tmp_line = ft_strjoin(line, "\n");
	ft_putstr_fd(tmp_line, fd);
	free(tmp_line);
}

int	has_var(char *str)
{
	if (!str)
		return (1);
	if (get_i_var(str) != -1)
		return (1);
	return (0);
}

char	*get_exp_line(char *line, t_prompt *p, t_command *cmd)
{
	char	*tmp;
	char	*exp_line;

	exp_line = ft_strdup(line);
	if (!cmd->heredoc_expand)
		return (exp_line);
	while (has_var(exp_line))
	{
		tmp = exp_line;
		exp_line = expand_heredoc(exp_line, p);
		free(tmp);
		if (!exp_line)
			return (NULL);
	}
	return (exp_line);
}

int	write_in_heredoc(t_command *cmd, t_prompt *p)
{
	char	*line;
	char	*exp_line;
	int		line_nbr;

	line_nbr = 0;
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			err_msg_heredoc(line_nbr, cmd);
			break ;
		}
		if (check_line(line, cmd->heredoc_delimiter))
		{
			free(line);
			break ;
		}
		exp_line = get_exp_line(line, p, cmd);
		if (!exp_line)
			break ;
		write_in_heredocsub1(exp_line, line, cmd, &line_nbr);
	}
	return (0);
}
