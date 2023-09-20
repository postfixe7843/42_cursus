/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:28:36 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 19:04:00 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	envsize(char **envp)
{
	int		i;

	i = 0;
	while ((envp)[i])
		i++;
	return (i);
}

int	mini_env(t_prompt *p, t_command *cmd)
{
	int		i;
	int		ret;
	char	*env;

	i = 0;
	ret = EXIT_SUCCESS;
	if (cmd->cmd && cmd->cmd[1])
	{
		error_msg("env", 0, NULL, "too many arguments");
		return (127);
	}
	env = ft_strdup("/usr/bin/env");
	if (!env)
		return (1);
	mini_setenv("_", env, &p->env);
	free(env);
	while (p->env[i])
	{
		ft_putendl_fd(p->env[i], 1);
		i++;
	}
	return (ret);
}

char	*mini_getenv(char *name, char **envp)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	len = ft_strlen(name);
	value = NULL;
	while (envp[i])
	{
		if (ft_strncmp(name, envp[i], len) == 0
			&& envp[i][len] == '=')
		{
			value = malloc(sizeof(char) * ft_strlen(envp[i]) - len);
			if (!value)
				return (error_malloc_null());
			ft_strlcpy(value, &envp[i][len + 1], ft_strlen(envp[i]) - len);
			return (value);
		}
		i++;
	}
	return (value);
}
