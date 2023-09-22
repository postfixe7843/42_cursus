/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:28:57 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/20 12:59:31 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{	
		while (envp[i])
		{
			free(envp[i]);
			i++;
		}
		free (envp);
	}
}

int	arg_is_valid(char *arg)
{
	int	error;

	error = 1;
	ft_atol_checker(arg, &error);
	if (error)
		return (0);
	return (1);
}

int	get_exit_status(char *arg)
{
	int	status;
	int	error;

	error = 0;
	if (arg == NULL)
		return (0);
	status = ft_atol_checker(arg, &error);
	if (status > 255)
		status = status % 256;
	else if (status < 0)
		status = 256 + status % 256;
	return (status);
}

int	is_valid(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (i > 1)
		{
			error_msg("exit", 0, NULL, "too many arguments");
			return (1);
		}
		if (!arg_is_valid(cmd[i]))
		{
			error_msg("exit", 0, cmd[i], "numeric argument required");
			return (2);
		}
		i++;
	}
	return (0);
}

int	mini_exit(t_prompt *p, t_command *cmd)
{
	int	ret;
	int	tmp;

	ft_putstr_fd("exit\n", 2);
	if (!cmd)
	{
		tmp = p->last_pipeline_status;
		free_prompt(p);
		exit(tmp);
	}
	ret = is_valid(cmd->cmd);
	if (ret == 1)
		return (ret);
	if (ret == 0)
		ret = get_exit_status(cmd->cmd[1]);
	if (ret == 0)
		ret = p->last_pipeline_status;
	free_prompt(p);
	exit(ret);
}
