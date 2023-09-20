/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:41:12 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/20 12:34:13 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_cmd(t_prompt *p, int i)
{
	int		j;
	char	*command_to_execute;

	j = 0;
	command_to_execute = NULL;
	if (!valid_file_redir(p->cmds[i]))
		exit(1);
	if (is_builtin(p->cmds[i]->cmd[0]))
		exit(exec_builtins(p, p->cmds[i]));
	else
	{
		check_path(p, p->cmds[i]->cmd);
		while (p->splitted_path[j])
		{
			if (p->cmds[i]->cmd[0][0] != '.' && p->cmds[i]->cmd[0][0] != '/')
				command_to_execute = ft_strjoin(p->splitted_path[j],
						p->cmds[i]->cmd[0]);
			if (command_to_execute && access(command_to_execute, X_OK) == 0)
				execve(command_to_execute, p->cmds[i]->cmd, p->env);
			else if (p->splitted_path[j + 1] == NULL && p->cmds[i]->cmd[0])
				check_cmd_not_found(p->cmds[i]->cmd[0]);
			free(command_to_execute);
			j++;
		}
	}
}

void	setup_fd(int **pipes, int i, int n)
{
	int	j;

	j = 0;
	if (i != 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i != n - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	while (j < n - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	init_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		pipe(pipes[i]);
		i++;
	}
}

void	start_pipeline(int **pipes, pid_t *childs, t_prompt *p)
{
	int	n;

	n = get_cmds_nbr2(p->cmds);
	p->pid = -1;
	if (n == 1 && is_builtin(p->cmds[0]->cmd[0]))
	{
		p->pid = 0;
		setup_redir(p->cmds[0], p);
		p->last_pipeline_status = exec_builtins(p, p->cmds[0]);
		reset_fds(p->cmds[0]);
		return ;
	}
	init_pipes(pipes, n);
	start_pipeline_sub1(n, p, pipes, childs);
}

void	start_pipeline_sub1(int n, t_prompt *p, int **pipes, int *childs)
{
	int	i;

	i = 0;
	while (i < n)
	{
		p->pid = -1;
		childs[i] = fork();
		if (childs[i] == 0)
		{
			p->pid = childs[i];
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			setup_fd(pipes, i, n);
			setup_redir(p->cmds[i], p);
			exec_cmd(p, i);
			close_fds(p->cmds[i], 0);
			close_fds(p->cmds[i], 1);
			reset_fds(p->cmds[i]);
		}
		i++;
	}
}
