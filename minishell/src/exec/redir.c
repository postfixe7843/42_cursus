/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:37:25 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/14 12:58:47 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_file_redir(t_command *cmd)
{
	if ((cmd->in_file && cmd->in_fd == -1)
		|| (cmd->out_file && cmd->out_fd == -1))
		return (0);
	return (1);
}

void	setup_redir(t_command *cmd, t_prompt *p)
{
	cmd->stdout_saved = dup(STDOUT_FILENO);
	cmd->stdin_saved = dup(STDIN_FILENO);
	if (cmd->stdout_saved == -1)
		error_msg(NULL, 0, NULL, strerror(errno));
	if (cmd->stdin_saved == -1)
		error_msg(NULL, 0, NULL, strerror(errno));
	if (cmd->in_fd != -1)
	{
		if (dup2(cmd->in_fd, STDIN_FILENO) == -1)
			error_msg(NULL, 0, NULL, strerror(errno));
	}
	if (cmd->out_fd != -1)
	{
		if (dup2(cmd->out_fd, STDOUT_FILENO) == -1)
			error_msg(NULL, 0, NULL, strerror(errno));
	}
	redir_in(cmd, p);
	redir_out(cmd, -1, p);
}

int	redir_out(t_command *cmd, int append, t_prompt *p)
{
	if (!cmd->out_file)
		return (1);
	if (append == 1)
		cmd->out_fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (append == 0)
		cmd->out_fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out_fd == -1)
	{
		cmd->out_fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (append == -1 && p && p->pid == 0)
		{
			error_msg(NULL, 0, cmd->out_file, strerror(errno));
			p->pid = -1;
			p->last_pipeline_status = 1;
		}
		return (1);
	}
	p->pid = -1;
	return (0);
}

int	redir_in(t_command *cmd, t_prompt *p)
{
	if (!cmd->in_file)
		return (1);
	if (cmd->in_fd == -1)
		cmd->in_fd = open(cmd->in_file, O_RDONLY);
	if (cmd->in_fd == -1)
	{
		if (p && p->pid == 0)
		{
			error_msg(NULL, 0, cmd->in_file, strerror(errno));
			p->last_pipeline_status = 1;
		}
		return (1);
	}
	return (0);
}
