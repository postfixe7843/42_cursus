/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:46:30 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 14:31:57 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	delete_quote(char *str, int index)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	if (!str)
		return ;
	while (i < index)
	{
		str[i] = str[i];
		i++;
	}
	while (index < len)
	{
		i = index + 1;
		str[index] = str[i];
		index++;
	}
	str[index] = 0;
}

void	check_quotes(char *val, int *open_sq, int *open_dq, int *i)
{
	if (val[*i] == '\"' && *open_dq == 0 && *open_sq == 0)
	{
		delete_quote(val, *i);
		*open_dq = 1;
	}
	else if (val[*i] == '\"' && *open_dq == 1 && *open_sq == 0)
	{
		delete_quote(val, *i);
		*open_dq = 0;
	}
	else if (val[*i] == '\'' && *open_sq == 0 && *open_dq == 0)
	{
		delete_quote(val, *i);
		*open_sq = 1;
	}
	else if (val[*i] == '\'' && *open_sq == 1 && *open_dq == 0)
	{
		delete_quote(val, *i);
		*open_sq = 0;
	}
	else
		*i = *i + 1;
}

void	handle_quotes(t_token *tok)
{
	int		i;
	char	*new_value;
	int		open_squote;
	int		open_dquote;

	if (tok->type == TOKEN_KEEP_Q)
		return ;
	i = 0;
	if (!strchr(tok->value, '\'') && !strchr(tok->value, '\"'))
		return ;
	new_value = ft_strdup(tok->value);
	if (!new_value)
		return ;
	open_squote = 0;
	open_dquote = 0;
	while (new_value[i])
		check_quotes(new_value, &open_squote, &open_dquote, &i);
	free(tok->value);
	tok->value = new_value;
}
