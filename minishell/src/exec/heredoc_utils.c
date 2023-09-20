/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:39:02 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/19 11:57:37 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	err_msg_heredoc(int line_nbr, t_command *cmd)
{
	char	*err_msg;
	char	*itoa_result;

	itoa_result = ft_itoa(line_nbr);
	err_msg = ft_strdup("minishell: warning: ");
	err_msg = join_msg(err_msg, "here-document at line ");
	err_msg = join_msg(err_msg, itoa_result);
	err_msg = join_msg(err_msg, " delimited by end-of-file (wanted `");
	err_msg = join_msg(err_msg, cmd->heredoc_delimiter);
	err_msg = join_msg(err_msg, "\')");
	err_msg = join_msg(err_msg, "\n");
	ft_putstr_fd(err_msg, 2);
	free(itoa_result);
	free(err_msg);
}

void	clean_old_heredoc(t_command *cmd)
{
	if (cmd->heredoc_delimiter)
	{
		close_fds(cmd, 0);
		free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = NULL;
		if (cmd->in_file)
		{
			unlink(cmd->in_file);
			free(cmd->in_file);
			cmd->in_file = NULL;
		}
	}
}

int	len_var(char *str)
{
	int		i;
	int		len;
	char	*start_var;

	i = 1;
	len = 0;
	start_var = ft_strchr(str, '$');
	if (!start_var)
		return (0);
	if (start_var[1]
		&& (ft_isdigit(start_var[1]) || start_var[1] == '?'))
		return (1);
	while (start_var[i] && (ft_isalnum(start_var[i]) || start_var[i] == '_'))
	{
		i++;
		len++;
	}
	return (len);
}

int	get_i_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && len_var(&str[i]) > 0)
			return (i);
		i++;
	}
	return (-1);
}
