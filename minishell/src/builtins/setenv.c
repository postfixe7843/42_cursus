/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:54:47 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/17 18:17:39 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*new_var_env(char *name, char *value)
{
	char	*tmp;
	char	*var;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	if (value == NULL)
		var = ft_strjoin(tmp, "");
	else
		var = ft_strjoin(tmp, value);
	free(tmp);
	return (var);
}

static char	**setenv_cpy(char **envp, int add, char *var_to_add)
{
	char	**mini_envp;
	int		i;
	int		envp_size;

	i = 0;
	envp_size = envsize(envp);
	mini_envp = malloc(sizeof(char *) * (envp_size + 1 + add));
	if (!mini_envp)
		return (error_malloc_null());
	while (i < envp_size)
	{
		mini_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	if (add == 1)
		mini_envp[i] = var_to_add;
	mini_envp[i + add] = NULL;
	return (mini_envp);
}

void	overwrite_var_value(char *name, char *var, char **envp)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0
			&& envp[i][len] == '=')
		{
			free(envp[i]);
			envp[i] = var;
		}
		i++;
	}
}

void	mini_setenv(char *name, char *value, char ***envp)
{
	char	*var;
	char	*get_env;
	char	**tmp_env;

	if (name == NULL || name[0] == '\0')
		return ;
	var = new_var_env(name, value);
	if (!var)
		return (error_malloc_void());
	get_env = mini_getenv(name, *envp);
	if (get_env == NULL)
	{
		tmp_env = *envp;
		*envp = setenv_cpy(*envp, 1, var);
		free_envp(tmp_env);
	}
	else
		overwrite_var_value(name, var, *envp);
	free(get_env);
	return ;
}

char	**init_mini_envp(char **envp)
{
	return (setenv_cpy(envp, 0, NULL));
}
