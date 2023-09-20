/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:33:16 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/20 12:57:27 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_not_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (0);
	return (1);
}

t_token	*create_token(char *str, int *index)
{
	while (str[*index]
		&& ((str[*index] == ' ' || str[*index] == '\t')
			&& !is_space_in_token(str, *index)))
		(*index)++;
	if (str[*index] == '\0')
		return (NULL);
	if ((str[*index] == '>'
			&& str[*index + 1] == '>') || (str[*index] == '<'
			&& str[*index + 1] == '<'))
		return (create_double_char_token(str, index));
	else if (str[*index] == '|' || str[*index] == '>' || str[*index] == '<')
		return (create_single_char_token(str, index));
	else if (str[*index] == '\'' || str[*index] == '\"')
		return (create_quotes_token(str, index));
	return (create_word_token(str, index));
}

t_token	**err_msg_token(char *token_value, t_prompt *p)
{
	char	*msg;

	msg = ft_strjoin("syntax error near unexpected token `", token_value);
	msg = join_msg(msg, "'");
	error_msg(NULL, 0, NULL, msg);
	p->last_pipeline_status = 2;
	free(msg);
	return (NULL);
}

t_token	**err_msg_token1(char *str, t_prompt *p, t_token **res, int index)
{
	int	i;

	i = 0;
	res[index + 1] = NULL;
	err_msg_token(str, p);
	while (res[i])
	{
		free(res[i]->value);
		free(res[i]->str_input);
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

void	init_token(t_token *token)
{
	token->str_input = NULL;
	token->value = NULL;
	token->i_expand = -1;
	token->type = -1;
}
