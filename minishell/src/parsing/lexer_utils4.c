/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:50:00 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/19 13:26:45 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	word_token_dquotes(char *str, t_token *res, int *index, int *i)
{
	res->value[*i] = str[*index];
	(*i)++;
	(*index)++;
	while (str[*index] && str[*index] != '\"')
	{
		res->value[*i] = str[*index];
		(*index)++;
		(*i)++;
	}
	res->value[*i] = str[*index];
	(*i)++;
	(*index)++;
}

t_token	*create_word_token(char *str, int *index)
{
	t_token	*res;
	int		i;

	res = malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	init_token(res);
	res->type = TOKEN_WORD;
	i = word_token_len(str, *index);
	res->value = malloc(sizeof(char) * (i - *index + 1));
	if (!res->value)
		return (NULL);
	i = 0;
	while (str[*index] && is_in_token(str, *index))
	{
		if (str[*index] == '\"')
			word_token_dquotes(str, res, index, &i);
		else if (str[*index] == '\'')
			word_token_squotes(str, res, index, &i);
		else
			res->value[i++] = str[(*index)++];
	}
	res->value[i] = '\0';
	return (res);
}

t_token	**lexer_loop(int *index, char *str, int *i, t_prompt *p)
{
	t_token	**res;

	res = (t_token **)malloc(sizeof(t_token *) * MAX_TOKEN);
	while (str[*index] != '\0' && *i < MAX_TOKEN)
	{
		res[*i] = create_token(str, index);
		if (res[*i] == NULL)
			return (res);
		res = checks(i, res, p);
		if (!res)
			return (NULL);
		(*i)++;
	}
	if (*i >= MAX_TOKEN)
		return (err_msg_max_token(p, res, *i));
	res = finish_token(res, i, p);
	return (res);
}

t_token	**checks(int *i, t_token **res, t_prompt *p)
{
	if (*i > 0 && res[*i] && res[*i]->type == 0
		&& (res[*i - 1]->type == 1 || res[*i - 1]->type == 2
			|| res[*i - 1]->type == 3 || res[*i - 1]->type == 4))
		res[*i]->type = TOKEN_FILE;
	else if (*i == 0 && res[*i]->type == 6)
		return (err_msg_token1(res[*i]->value, p, res, *i));
	else if (*i > 0 && res[*i] && res[*i]->type
		== 6 && res[*i - 1]->type == 6)
		return (err_msg_token1(res[*i]->value, p, res, *i));
	else if (*i > 0 && res[*i] && res[*i]->type == 6 && (res[*i - 1]->type
			== 2 || res[*i - 1]->type == 3 || res[*i - 1]->type == 1))
		return (err_msg_token1(res[*i]->value, p, res, *i));
	else if (*i > 0 && (res[*i]->type == 2 || res[*i]->type == 3)
		&& (res[*i - 1]->type == 2 || res[*i - 1]->type == 3))
		return (err_msg_token1(res[*i]->value, p, res, *i));
	else if (*i > 0 && (res[*i]->type == 1 || res[*i]->type == 4)
		&& (res[*i - 1]->type == 1 || res[*i - 1]->type == 4
			|| res[*i - 1]->type == 3 || res[*i - 1]->type == 2))
		return (err_msg_token1(res[*i]->value, p, res, *i));
	return (res);
}

t_token	**finish_token(t_token **res, int *i, t_prompt *p)
{
	res[*i] = NULL;
	if (res[*i - 1] && (res[*i - 1]->type == 1 || res[*i - 1]->type == 2
			|| res[*i -1]->type == 3 || res[*i -1]->type == 4))
	{
		err_msg_token("newline", p);
		free_tokens2(res);
		return (NULL);
	}
	else if (res[*i - 1] && res[*i - 1]->type == TOKEN_PIPE)
	{
		err_msg_token(res[*i - 1]->value, p);
		free_tokens2(res);
		return (NULL);
	}
	return (res);
}
