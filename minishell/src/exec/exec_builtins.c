/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:12:36 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 19:00:05 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtins(t_prompt *p, t_command *cmd)
{
	int	ret;

	ret = 0;
	if (!valid_file_redir(cmd))
		return (1);
	if (is_builtin(cmd->cmd[0]))
	{
		if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
			ret = mini_echo(cmd);
		else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
			ret = mini_cd(p, cmd, cmd->cmd[1]);
		else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
			ret = mini_pwd(p, cmd);
		else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
			ret = mini_export(p, cmd);
		else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
			ret = mini_unset(p, cmd);
		else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
			ret = mini_env(p, cmd);
		else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
			ret = mini_exit(p, cmd);
	}
	return (ret);
}
