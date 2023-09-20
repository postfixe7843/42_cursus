/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:45:54 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/19 14:50:55 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_between_dquote(char *str, int start)
{
	int		i;
	int		open_squote;
	int		open_dquote;

	i = 0;
	if (!str)
		return (0);
	open_squote = 0;
	open_dquote = 0;
	while (i < start)
	{
		if (str[i] == '\"' && open_dquote == 0 && open_squote == 0)
			open_dquote = 1;
		else if (str[i] == '\"' && open_dquote == 1 && open_squote == 0)
			open_dquote = 0;
		else if (str[i] == '\'' && open_squote == 0 && open_dquote == 0)
			open_squote = 1;
		else if (str[i] == '\'' && open_squote == 1 && open_dquote == 0)
			open_squote = 0;
		i++;
	}
	if (open_dquote == 1)
		return (1);
	return (0);
}

int	is_between_squote(char *str, int start)
{
	int		i;
	int		open_squote;
	int		open_dquote;

	i = 0;
	open_squote = 0;
	open_dquote = 0;
	while (i < start)
	{
		if (str[i] == '\"' && open_dquote == 0 && open_squote == 0)
			open_dquote = 1;
		else if (str[i] == '\"' && open_dquote == 1 && open_squote == 0)
			open_dquote = 0;
		else if (str[i] == '\'' && open_squote == 0 && open_dquote == 0)
			open_squote = 1;
		else if (str[i] == '\'' && open_squote == 1 && open_dquote == 0)
			open_squote = 0;
		i++;
	}
	if (open_squote == 1)
		return (1);
	return (0);
}

int	len_varname(char *str, int start_i)
{
	int		i;
	int		len;
	char	*start_var;

	i = 1;
	len = 0;
	start_var = &str[start_i];
	if (!start_var)
		return (0);
	if (start_var[1]
		&& (ft_isdigit(start_var[1]) || start_var[1] == '?'))
		return (1);
	while (start_var[i] && (ft_isalnum(start_var[i]) || start_var[i] == '_'))
	{
		i++;
		len++;
	}
	return (len);
}

int	get_i_var_toexpand(char *str, t_prompt *p, int count)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_between_squote(str, i) == 0
			&& (is_expandable(str, i, p)
				|| (!is_expandable(str, i, p) && count == 0)))
		{
			if ((i > 0 && str[i + 1] == '\'' && str[i - 1] == '\'')
				|| (i > 0 && str[i + 1] == '\"' && str[i - 1] == '\"')
				|| !(ft_isalpha(str[i + 1])
					|| str[i + 1] == '_' || str[i + 1] == '?'))
				return (-1);
			return (i);
		}
		i++;
	}
	return (-1);
}
