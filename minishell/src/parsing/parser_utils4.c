/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:31:49 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/17 21:37:56 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	split_token(t_token *tok, char *str, int *j, t_command *res)
{
	char	**tmp;
	int		i;

	tmp = ft_split(str, ' ');
	if (tmp && !tmp[0] && str && is_between_dquote(tok->str_input, 1))
	{
		res->cmd[*j] = ft_strdup("");
		(*j)++;
	}
	i = 0;
	while (tmp[i])
	{
		res->cmd[*j] = ft_strdup(tmp[i]);
		free(tmp[i]);
		(*j)++;
		i++;
	}
	(*j)--;
	free(tmp);
	tmp = NULL;
}

int	is_redir_redirout(int *index, t_prompt *p, t_command *res, int j)
{
	(*index)++;
	clean_old_file(res, 0);
	res->out_file = parse_file_token(p->tokens[*index]);
	if (redir_out(res, 0, p))
	{
		res->cmd[j] = NULL;
		while (p->tokens[*index] && p->tokens[*index]->type != TOKEN_PIPE)
			(*index)++;
		return (1);
	}
	(*index)++;
	return (0);
}

int	is_redir_redirapp(int *index, t_prompt *p, t_command *res, int j)
{
	(*index)++;
	clean_old_file(res, 0);
	res->out_file = parse_file_token(p->tokens[*index]);
	if (redir_out(res, 1, p))
	{
		res->cmd[j] = NULL;
		while (p->tokens[*index] && p->tokens[*index]->type != TOKEN_PIPE)
			(*index)++;
		return (1);
	}
	(*index)++;
	return (0);
}

int	is_redir_redirin(int *index, t_prompt *p, t_command *res, int j)
{
	(*index)++;
	if (!p->tokens[*index] || !res)
		return (1);
	clean_old_file(res, 1);
	res->in_file = parse_file_token(p->tokens[*index]);
	if (redir_in(res, NULL))
	{
		res->cmd[j] = NULL;
		while (p->tokens[*index] && p->tokens[*index]->type != TOKEN_PIPE)
		{
			p->tokens[*index]->type = TOKEN_FILE;
			(*index)++;
		}
		return (1);
	}
	(*index)++;
	return (0);
}

t_command	*is_redir(t_prompt *p, int *index, int j, t_command *res)
{
	while (p->tokens[*index] != NULL && (p->tokens[*index]->type != TOKEN_PIPE))
	{
		if (p->tokens[*index]->type == TOKEN_REDIROUT)
		{
			if (is_redir_redirout(index, p, res, j))
				return (res);
		}
		else if (p->tokens[*index]->type == TOKEN_REDIRAPP)
		{
			if (is_redir_redirapp(index, p, res, j))
				return (res);
		}
		else if (p->tokens[*index]->type == TOKEN_REDIRIN)
		{
			if (is_redir_redirin(index, p, res, j))
				return (res);
		}
		else if (p->tokens[*index]->type == TOKEN_HEREDOC)
			return (is_heredoc(p, index, j, res));
		else
			res->cmd[j++] = p->tokens[(*index)++]->value;
	}
	return (res);
}
