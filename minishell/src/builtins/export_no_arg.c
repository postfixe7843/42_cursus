/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:41:21 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/15 15:01:36 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	alpha_sort(char **strs, int size)
{
	int		i;
	int		j;
	char	*current;
	char	*tmp;

	i = 1;
	while (i >= 1 && i < size && strs[i])
	{
		j = i;
		current = ft_strdup(strs[i]);
		while (j > 0 && strs[j - 1] && ft_strcmp(strs[j - 1], current) > 0)
		{
			tmp = ft_strdup(strs[j - 1]);
			free(strs[j - 1]);
			strs[j - 1] = NULL;
			if (strs[j])
				free(strs[j]);
			strs[j] = tmp;
			j--;
		}
		if (strs[j])
			free(strs[j]);
		strs[j] = current;
		i++;
	}
}

char	**env_alpha_sort(char **strs, int size)
{
	int		i;
	char	**sorted_env;

	i = 0;
	if (!strs)
		return (NULL);
	sorted_env = malloc(sizeof(char *) * (size + 1));
	if (!sorted_env)
		return (NULL);
	while (strs[i])
	{
		sorted_env[i] = ft_strdup(strs[i]);
		i++;
	}
	sorted_env[i] = NULL;
	alpha_sort(sorted_env, size);
	return (sorted_env);
}

char	*join_key_value(char *var, char	*joined_export)
{
	int		i;
	int		first_quote;
	char	*c_ptr;

	i = 0;
	first_quote = 0;
	while (var[i])
	{
		c_ptr = ft_substr(var, i, 1);
		joined_export = join_msg(joined_export, c_ptr);
		free(c_ptr);
		if (var[i] == '=' && first_quote == 0)
		{
			joined_export = join_msg(joined_export, "\"");
			first_quote = 1;
		}
		i++;
	}
	joined_export = join_msg(joined_export, "\"");
	joined_export = join_msg(joined_export, "\n");
	return (joined_export);
}

char	*join_export(char **sorted_env)
{
	int		i;
	char	*joined_export;

	i = 0;
	if (!sorted_env)
		return (NULL);
	joined_export = ft_strdup("");
	if (!joined_export)
		return (NULL);
	while (sorted_env[i])
	{
		if (ft_strncmp(sorted_env[i], "_=", 2) != 0)
		{
			joined_export = join_msg(joined_export, "declare -x ");
			joined_export = join_key_value(sorted_env[i], joined_export);
		}
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
	return (joined_export);
}

void	export_no_arg(char **env)
{
	char	**sorted_env;
	char	*export_env;

	if (!env)
		return ;
	sorted_env = env_alpha_sort(env, envsize(env));
	if (!sorted_env)
		return ;
	export_env = join_export(sorted_env);
	if (!export_env)
		return ;
	ft_putstr_fd(export_env, 1);
	free(export_env);
}
