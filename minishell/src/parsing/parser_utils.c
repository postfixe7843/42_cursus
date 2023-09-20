/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:56:27 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/18 17:08:24 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_filename(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	if (!token->value[i])
		return (0);
	while (token->value[i])
	{
		if (!ft_isascii(token->value[i]) && token->value[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	del_dollar_str_input(t_token *tok)
{
	int		i;
	char	*dol;
	char	*sub_str;
	char	*to_free;

	i = 0;
	while (tok->str_input[i])
	{
		if (dollar_to_delete(tok->str_input, i))
		{
			sub_str = ft_substr(tok->str_input, 0, i);
			if (!sub_str)
				return ;
			dol = ft_strdup(&tok->str_input[i + 1]);
			if (!dol || !dol[0] || !dol[1])
				return ;
			to_free = tok->str_input;
			tok->str_input = join_msg(sub_str, dol);
			free(to_free);
			free(dol);
		}
		i++;
	}
}

char	*parse_delim_heredoc(t_token *token, t_command *res)
{
	int		i;
	char	*delim;

	i = 0;
	del_dollar_str_input(token);
	while (token->str_input[i])
		i++;
	delim = malloc(sizeof(char) * i + 1);
	if (!delim)
		return (NULL);
	i = 0;
	while (token->str_input[i])
	{
		delim[i] = token->str_input[i];
		i++;
	}
	delim[i] = '\0';
	if (ft_strchr(delim, '\"')
		|| ft_strchr(delim, '\''))
		res->heredoc_expand = 0;
	return (delim);
}

int	get_char_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*parse_file_token(t_token *token)
{
	int		i;
	char	*filename;

	i = 0;
	while (token->value[i])
		i++;
	filename = malloc(sizeof(char) * i + 1);
	if (!filename)
		return (NULL);
	copy_into_filename(filename, token->value);
	if (ft_strchr(filename, ' ') && !is_between_dquote(token->str_input,
			get_char_index(token->str_input, ' '))
		&& !is_between_dquote(token->str_input,
			get_char_index(token->str_input, '$')))
	{
		error_msg(NULL, 0, token->str_input, "ambiguous redirect");
		free(filename);
		return (NULL);
	}
	return (filename);
}
