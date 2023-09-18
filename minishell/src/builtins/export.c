/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:26:49 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/13 10:39:11 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_chars(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		free(chars[i]);
		i++;
	}
	free(chars);
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (key == NULL || ft_isdigit(key[0])
		|| !(ft_isalnum(key[i]) || key[i] == '_'))
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (ft_isalnum(key[i]) || key[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

char	**set_key_value(char *str)
{
	char	**key_value;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		key_value = malloc(sizeof(char *) * 3);
		if (key_value == NULL)
			return (NULL);
		key_value[0] = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(key_value[0], &str[0], i + 1);
	}
	else
		return (NULL);
	key_value[1] = malloc(sizeof(char) * (ft_strlen(str) - i));
	ft_strlcpy(key_value[1], &str[i + 1], ft_strlen(str) - i);
	key_value[2] = NULL;
	return (key_value);
}

int	mini_export(t_prompt *p, t_command *cmd)
{
	int		i;
	char	**key_value;
	int		ret;

	i = 1;
	ret = EXIT_SUCCESS;
	if (cmd->cmd[i] == NULL)
		export_no_arg(p->env);
	while (cmd->cmd[i])
	{
		if (is_valid_key(cmd->cmd[i]) == 0)
			return (error_ret("export", cmd->cmd[i],
					"not a valid identifier", 1));
		key_value = set_key_value(cmd->cmd[i]);
		if (key_value != NULL)
		{
			mini_setenv(key_value[0], key_value[1], &p->env);
			free_chars(key_value);
		}
		else
			ret = EXIT_SUCCESS;
		i++;
	}
	return (ret);
}
