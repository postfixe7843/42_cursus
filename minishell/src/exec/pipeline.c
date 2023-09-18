/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:41:12 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 17:30:44 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipeline(t_prompt *p)
{
	char	*tmp;

	p->pipes = create_pipes(p->nb_cmd);
	p->childs = create_childs(p->nb_cmd);
	if (!p->pipes || !p->childs)
	{
		error_malloc_void();
		return ;
	}
	tmp = mini_getenv("PATH", p->env);
	p->splitted_path = ft_split(tmp, ':');
	free(tmp);
	if (p->splitted_path)
		append_backslash(p->splitted_path);
	if (has_invalid_cmd(p->cmds))
	{
		p->pid = 0;
		setup_redir(p->cmds[0], p);
		p->pid = -1;
		reset_fds(p->cmds[0]);
		return ;
	}
	start_pipeline(p->pipes, p->childs, p);
	stop_pipeline(p->pipes, p->childs, p->nb_cmd, p);
}

void	check_path(t_prompt *p, char **cmd)
{
	if (!cmd || !cmd[0])
		exit(1);
	if (ft_strcmp(cmd[0], ".") == 0 || ft_strcmp(cmd[0], "..") == 0
		|| ft_strcmp(cmd[0], "") == 0)
	{
		error_msg(NULL, 0, cmd[0], "command not found");
		exit(127);
	}		
	if (is_dir(p, cmd[0]))
	{
		error_msg(NULL, 0, cmd[0], "Is a directory");
		exit(126);
	}
	if (access(cmd[0], X_OK) == 0)
	{
		if (ft_strcmp(cmd[0], "./minishell") == 0)
			increment_shlvl(p);
		execve(cmd[0], cmd, p->env);
	}
	else if (!p->splitted_path)
	{
		error_msg(NULL, 0, cmd[0], strerror(errno));
		exit(127);
	}
}

void	increment_shlvl(t_prompt *p)
{
	int		shlvl;
	char	*res;

	shlvl = ft_atoi(mini_getenv("SHLVL", p->env));
	shlvl++;
	res = ft_itoa(shlvl);
	mini_setenv("SHLVL", res, &p->env);
}
