/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:54:43 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/21 12:26:30 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*create_cmd(t_prompt *p, int *index)
{
	t_command	*res;

	res = malloc(sizeof(t_command));
	if (!res)
		return (NULL);
	part1(p, index, res);
	return (part2(p, index, res));
}

void	part1(t_prompt *p, int *index, t_command *res)
{
	int	x;
	int	i;

	x = 0;
	init_cmd(res);
	if (p->tokens[*index] && (p->tokens[*index]->type == TOKEN_PIPE))
		(*index)++;
	i = *index;
	res->cmd = (char **)malloc(sizeof(char *)
			* ((get_cmd_len(p->tokens, i) + 1)));
	if (res->cmd != NULL)
	{
		while (x < get_cmd_len(p->tokens, i) + 1)
		{
			res->cmd[x] = NULL;
			x++;
		}
	}
}

t_command	*part2(t_prompt *p, int *i, t_command *res)
{
	int	j;

	j = 0;
	while (p->tokens[*i] && p->tokens[*i]->type != TOKEN_PIPE)
	{
		if (p->tokens[*i]->type == 2 || p->tokens[*i]->type == 3
			|| p->tokens[*i]->type == 1)
			return (is_redir(p, i, j, res));
		else if (p->tokens[*i]->type == 4)
			return (is_heredoc(p, i, j, res));
		if (p->tokens[*i]->type == TOKEN_EXPANDED)
			split_token(p->tokens[*i], p->tokens[*i]->value, &j, res);
		else
		{
			res->cmd[j] = p->tokens[*i]->value;
		}
		j++;
		(*i)++;
	}
	res->cmd[j] = NULL;
	return (res);
}

t_command	*is_heredoc(t_prompt *p, int *index, int j, t_command *res)
{
	(*index)++;
	while (p->tokens[*index] && p->tokens[*index]->type != TOKEN_PIPE)
	{
		if (p->tokens[*index] && p->tokens[*index]->type == TOKEN_PIPE)
			break ;
		if (p->tokens[*index] && p->tokens[*index]->type == TOKEN_REDIRAPP)
			is_redir_redirapp(index, p, res, j);
		else if (p->tokens[*index] && p->tokens[*index]->type == TOKEN_REDIROUT)
			is_redir_redirout(index, p, res, j);
		if (p->tokens[*index] && p->tokens[*index]->type == TOKEN_HEREDOC)
			(*index)++;
		if (p->tokens[*index] && p->tokens[*index - 1]->type == TOKEN_HEREDOC)
			is_heredoc_sub1(res, p, index);
		else if (p->tokens[*index] && p->tokens[*index]->type == TOKEN_WORD)
		{
			res->cmd[j] = p->tokens[*index]->value;
			(*index)++;
			j++;
		}
	}
	res->cmd[j] = NULL;
	if (!p->tokens[*index])
		return (res);
	return (res);
}

void	is_heredoc_sub1(t_command *res, t_prompt *p, int *index)
{
	clean_old_heredoc(res);
	res->heredoc_delimiter = parse_delim_heredoc(p->tokens[*index], res);
	g_status = 0;
	if (heredoc(res, p))
		return ;
	(*index)++;
}
