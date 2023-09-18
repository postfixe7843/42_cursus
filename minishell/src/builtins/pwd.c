/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:03:05 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/14 00:16:27 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	arg_valid(char *arg)
{
	if (ft_strcmp(arg, "-") == 0
		|| ft_strcmp(arg, "--") == 0)
		return (1);
	else if (arg[0] == '-')
		return (0);
	return (1);
}

int	mini_pwd(t_prompt *p, t_command *cmd)
{
	char	cwd[1024];
	int		ret;
	char	*ss;

	ret = EXIT_SUCCESS;
	if (cmd->cmd[1] && !arg_valid(cmd->cmd[1]))
	{
		ss = ft_substr(cmd->cmd[1], 0, 2);
		error_msg("pwd", 0, ss, "invalid option");
		free(ss);
		return (2);
	}
	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(p->wd, 1);
	else
		ft_putendl_fd(p->wd, 1);
	return (ret);
}
