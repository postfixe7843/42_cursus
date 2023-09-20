/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:27:24 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 16:14:25 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**unsetenv_cpy(char **envp, char *var_to_unset)
{
	char	**mini_envp;
	int		i;
	int		j;
	int		envp_size;

	i = 0;
	j = 0;
	envp_size = envsize(envp);
	mini_envp = malloc(sizeof(char *) * envp_size);
	if (!mini_envp)
		return (error_malloc_null());
	while (i < envp_size)
	{
		if (!(ft_strncmp(var_to_unset, envp[i], ft_strlen(var_to_unset)) == 0
				&& envp[i][ft_strlen(var_to_unset)] == '='))
			mini_envp[j++] = ft_strdup(envp[i]);
		i++;
	}
	mini_envp[j] = NULL;
	free_envp(envp);
	return (mini_envp);
}

void	mini_unsetenv(char *name, char ***envp)
{
	char	*get_env;

	get_env = mini_getenv(name, *envp);
	if (get_env == NULL)
		return ;
	*envp = unsetenv_cpy(*envp, name);
	free(get_env);
}

int	mini_unset(t_prompt *p, t_command *cmd)
{
	int	i;
	int	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (cmd->cmd[i])
	{
		mini_unsetenv(cmd->cmd[i], &p->env);
		i++;
	}
	return (ret);
}
