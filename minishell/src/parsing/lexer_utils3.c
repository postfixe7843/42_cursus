/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:57 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/20 12:57:35 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_space_in_token(char *str, int i)
{
	int	space_in_token;

	space_in_token = 0;
	if (str[i] == ' ' && (is_between_dquote(str, i)
			|| is_between_squote(str, i)))
		space_in_token = 1;
	return (space_in_token);
}

int	operator_in_quotes(char *str, int i)
{
	int	flag;

	flag = 0;
	if (!is_not_operator(str[i]) && (is_between_dquote(str, i)
			|| is_between_squote(str, i)))
		flag = 1;
	return (flag);
}

int	is_in_token(char *str, int i)
{
	int	in_token;

	in_token = 0;
	if (operator_in_quotes(str, i) || ((str[i] != ' ' && str[i] != '\t'
				&& is_not_operator(str[i])) || is_space_in_token(str, i)))
		in_token = 1;
	return (in_token);
}

t_token	*create_single_char_token(char *str, int *index)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	init_token(res);
	if (str[*index] == '|')
		res->type = TOKEN_PIPE;
	else if (str[*index] == '>')
		res->type = TOKEN_REDIROUT;
	else if (str[*index] == '<')
		res->type = TOKEN_REDIRIN;
	res->value = malloc(sizeof(char) * 2);
	if (!res->value)
		return (NULL);
	res->value[0] = str[*index];
	res->value[1] = '\0';
	(*index)++;
	return (res);
}

t_token	*create_double_char_token(char *str, int *index)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (!res)
		return (NULL);
	init_token(res);
	if (str[*index] == '\0')
		return (NULL);
	else if (str[*index] == '>')
		res->type = TOKEN_REDIRAPP;
	else if (str[*index] == '<')
		res->type = TOKEN_HEREDOC;
	res->value = malloc(sizeof(char) * 3);
	if (!res->value)
		return (NULL);
	res->value[0] = str[*index];
	res->value[1] = str[*index + 1];
	res->value[2] = '\0';
	(*index)++;
	(*index)++;
	return (res);
}
