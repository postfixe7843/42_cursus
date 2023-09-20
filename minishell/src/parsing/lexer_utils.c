/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:30:02 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/19 14:50:03 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	build_quotes_token(char *str, int *index, t_token *res)
{
	int	i;

	i = 0;
	while (str[*index] && is_in_token(str, *index))
	{
		if (str[*index] == '\'')
		{
			res->value[i++] = str[(*index)++];
			while (str[*index] != '\'')
				res->value[i++] = str[(*index)++];
			res->value[i++] = str[(*index)++];
		}
		else if (str[*index] == '\"')
		{
			res->value[i++] = str[(*index)++];
			while (str[*index] != '\"')
				res->value[i++] = str[(*index)++];
			res->value[i++] = str[(*index)++];
		}
		else
			build_q_token_sub1(str, index, res, &i);
	}
	res->value[i] = '\0';
}

void	build_q_token_sub1(char *str, int *index, t_token *res, int *i)
{
	while (str[*index] && is_in_token(str, *index))
	{
		res->value[*i] = str[*index];
		(*i)++;
		(*index)++;
	}
}

t_token	*create_quotes_token(char *str, int *index)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	init_token(res);
	res->type = TOKEN_WORD;
	res->value = malloc(sizeof(char)
			* (get_quotes_token_len(str, index) - *index + 1));
	if (!res->value)
		return (NULL);
	build_quotes_token(str, index, res);
	return (res);
}

int	word_token_len(char *str, int i)
{
	while (str[i] && is_in_token(str, i))
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		else
			i++;
	}
	return (i);
}

void	word_token_squotes(char *str, t_token *res, int *index, int *i)
{
	res->value[*i] = str[*index];
	(*i)++;
	(*index)++;
	while (str[*index] && str[*index] != '\'')
	{
		res->value[*i] = str[*index];
		(*index)++;
		(*i)++;
	}
	res->value[*i] = str[*index];
	(*i)++;
	(*index)++;
}
