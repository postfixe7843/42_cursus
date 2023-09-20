/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:50:00 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/19 14:55:08 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	**lexer(char *str, t_prompt *p)
{
	t_token	**res;
	int		i;
	int		index;

	i = 0;
	index = 0;
	res = lexer_loop(&index, str, &i, p);
	if (!res)
		return (NULL);
	return (res);
}

void	free_tokens2(t_token **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]->value);
		free(res[i]->str_input);
		free(res[i]);
		i++;
	}
	free(res);
}

t_token	**err_msg_max_token(t_prompt *p, t_token **res, int index)
{
	int	i;

	i = 0;
	free(res[MAX_TOKEN - 1]->value);
	free(res[MAX_TOKEN - 1]->str_input);
	free(res[MAX_TOKEN - 1]);
	res[index - 1] = NULL;
	error_msg("error", 0, NULL, "command too long");
	while (res[i])
	{
		free(res[i]->value);
		free(res[i]->str_input);
		free(res[i]);
		i++;
	}
	free(res);
	p->last_pipeline_status = 1;
	return (NULL);
}

int	get_quotes_token_len(char *str, int *index)
{
	int	i;

	i = *index;
	while (str[i] && is_in_token(str, i))
	{
		if (str[i] == '\'')
		{
			while (str[i + 1] != '\'')
				i++;
			i += 2;
		}
		else if (str[i] == '\"')
		{
			while (str[i + 1] && str[i + 1] != '\"')
				i++;
			i += 2;
		}
		else
		{
			while (str[i] && is_in_token(str, i))
				i++;
		}
	}
	return (i);
}
