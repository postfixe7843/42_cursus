/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:56:05 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 16:55:17 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_quotes_after(char *str, int i)
{
	int	count_after;

	count_after = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count_after++;
		i++;
	}
	return (count_after);
}

int	dollar_to_delete(char *tok_value, int i)
{
	if (tok_value[i] == '$' && (i == 0 || (i > 0 && tok_value[i - 1] != '$'))
		&& ((tok_value[i + 1] == '"' && !is_between_dquote(tok_value, i))
			|| (tok_value[i + 1] == '\'' && !is_between_squote(tok_value, i))))
		return (1);
	return (0);
}

void	del_dollar(t_token *tok)
{
	int		i;
	char	*dol;
	char	*sub_str;
	char	*to_free;

	i = 0;
	while (tok->value[i])
	{
		if (dollar_to_delete(tok->value, i))
		{
			sub_str = ft_substr(tok->value, 0, i);
			if (!sub_str)
				return ;
			dol = ft_strdup(&tok->value[i + 1]);
			if (!dol || !dol[0] || !dol[1])
				return ;
			to_free = tok->value;
			tok->value = join_msg(sub_str, dol);
			free(to_free);
			free(dol);
		}
		i++;
	}
}

void	expander_sub1(t_token **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		handle_quotes(t[i]);
		if (i > 0 && t[i - 1] && t[i - 1]->type == TOKEN_REDIROUT)
			t[i]->type = TOKEN_FILE;
		i++;
	}
}
