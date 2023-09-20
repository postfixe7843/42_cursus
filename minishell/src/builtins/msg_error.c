/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:51:03 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/17 20:21:51 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*add_quotes(char *str, int quote)
{
	char	*with_quotes;
	char	*tmp;
	char	*str_dup;

	str_dup = NULL;
	if (str)
		str_dup = ft_strdup(str);
	if (!str_dup)
		return (NULL);
	if (!quote)
		return (str_dup);
	with_quotes = ft_strjoin("`", str);
	if (!with_quotes)
		return (NULL);
	tmp = with_quotes;
	with_quotes = ft_strjoin(with_quotes, "'");
	free(tmp);
	free(str_dup);
	if (!with_quotes)
		return (NULL);
	return (with_quotes);
}

char	*join_msg(char *msg, char *to_add)
{
	char	*tmp;

	if (!to_add)
		return (msg);
	tmp = msg;
	msg = ft_strjoin(tmp, to_add);
	if (tmp)
		free(tmp);
	return (msg);
}

void	error_msg(char *cmd, int quote, char *input, char *err_msg)
{
	char	*msg;
	char	*input_quote;

	msg = ft_strdup("minishell: ");
	if (cmd)
	{
		msg = join_msg(msg, cmd);
		msg = join_msg(msg, ": ");
	}
	input_quote = add_quotes(input, quote);
	if (input_quote)
	{
		msg = join_msg(msg, input_quote);
		msg = join_msg(msg, ": ");
		free(input_quote);
	}
	msg = join_msg(msg, err_msg);
	msg = join_msg(msg, "\n");
	ft_putstr_fd(msg, 2);
	free(msg);
}
