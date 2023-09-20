/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:51:06 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 11:31:58 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_var_name(char *str, int i)
{
	int		len;
	char	*var_name;

	len = len_varname(str, i);
	var_name = ft_substr(str, i, len + 1);
	return (var_name);
}

char	*get_var_toexpand(t_token *tok, char *str, t_prompt *p)
{
	int	i;

	i = get_i_var_toexpand(str, p, 0);
	if (i != -1)
	{
		if (!ft_strchr(tok->value, '='))
			tok->type = TOKEN_EXPANDED;
		return (&str[i]);
	}
	return (NULL);
}

int	is_in_value(char *var_name, char *var_value)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var_name);
	while (var_value[i])
	{
		if (ft_strncmp(var_name, &var_value[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_expandable(char *str, int i, t_prompt *p)
{
	char	*var_name;
	char	*var_value;
	int		ret;

	ret = 1;
	var_name = get_var_name(str, i);
	if (!var_name)
		return (0);
	var_value = mini_getenv(&var_name[1], p->env);
	if (!var_value)
	{
		free(var_name);
		return (1);
	}
	if (is_in_value(var_name, var_value))
		ret = 0;
	free(var_name);
	free(var_value);
	return (ret);
}
