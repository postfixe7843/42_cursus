/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:05:51 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/20 12:46:04 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clean_old_file(t_command *cmd, int in_file)
{
	if (cmd->out_file && !in_file)
	{
		free(cmd->out_file);
		cmd->out_file = NULL;
		close_fds(cmd, 1);
		close_fds(cmd, 0);
	}
	if (cmd->in_file && in_file)
	{
		free(cmd->in_file);
		cmd->in_file = NULL;
		close_fds(cmd, 0);
		close_fds(cmd, 1);
	}
}

void	reset_fds(t_command *cmd)
{
	if (cmd->stdout_saved != -1)
	{
		if (dup2(cmd->stdout_saved, STDOUT_FILENO) == -1)
			return ;
		close(cmd->stdout_saved);
		cmd->stdout_saved = -1;
	}
	if (cmd->stdin_saved != -1)
	{
		if (dup2(cmd->stdin_saved, STDIN_FILENO) == -1)
			return ;
		close(cmd->stdin_saved);
		cmd->stdin_saved = -1;
	}
	clean_old_file(cmd, 0);
	clean_old_heredoc(cmd);
}

void	close_fds(t_command *cmd, int out_fd)
{
	if (!cmd)
		return ;
	if (cmd->out_fd != -1 && out_fd)
	{
		close(cmd->out_fd);
		cmd->out_fd = -1;
	}
	if (cmd->in_fd != -1 && !out_fd)
	{
		close(cmd->in_fd);
		cmd->in_fd = -1;
	}	
}

int	valid_file_redir(t_command *cmd)
{
	if ((cmd->in_file && cmd->in_fd == -1)
		|| (cmd->out_file && cmd->out_fd == -1))
	{
		close_fds(cmd, 0);
		close_fds(cmd, 1);
		reset_fds(cmd);
		return (0);
	}
	return (1);
}
