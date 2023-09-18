/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:50:00 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/18 16:29:50 by nlence-l         ###   ########.fr       */
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
