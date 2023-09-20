/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:37:11 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/18 21:57:51 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	stop_pipeline(int **pipes, pid_t *childs, int n, t_prompt *p)
{
	int	i;
	int	ret;

	i = 0;
	ret = EXIT_SUCCESS;
	while (i < n - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (n == 1 && p->cmds[0] && is_builtin(p->cmds[0]->cmd[0]))
		return ;
	i = 0;
	while (i < n)
	{
		waitpid(childs[i], &ret, 0);
		i++;
	}
	if ((n > 1 && WIFEXITED(ret))
		|| (n == 1 && p->cmds[0] && !is_builtin(p->cmds[0]->cmd[0])))
		p->last_pipeline_status = WEXITSTATUS(ret);
}

int	has_invalid_cmd(t_command **cmds)
{
	int	i;
	int	no_valid;

	i = 0;
	no_valid = 0;
	while (cmds[i])
	{
		if (cmds[i]->cmd[0] == NULL)
			no_valid = 1;
		else
			no_valid = 0;
		i++;
	}
	return (no_valid);
}

int	**create_pipes(int num_commands)
{
	int	i;
	int	**res;

	i = 0;
	res = (int **)malloc(sizeof(int *) * (num_commands - 1));
	if (!res)
		return (NULL);
	while (i < (num_commands - 1))
	{
		res[i] = (int *)malloc(sizeof(int) * 2);
		if (!res[i])
			return (NULL);
		i++;
	}
	return (res);
}

pid_t	*create_childs(int num_commands)
{
	pid_t	*res;

	res = (int *)malloc(sizeof(int) * num_commands);
	if (!res)
		return (NULL);
	return (res);
}

void	free_pipes_and_childs(t_prompt *p)
{
	int	i;

	i = 0;
	if (p->pipes)
	{
		while (i < (p->nb_cmd - 1))
		{
			if (p->pipes[i])
				free(p->pipes[i]);
			i++;
		}
		free(p->pipes);
	}
	if (p->childs)
		free(p->childs);
}
