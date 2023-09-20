/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:29:38 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/19 14:49:24 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_lastarg(t_prompt *p)
{
	int		i;
	char	*val;

	i = 0;
	val = NULL;
	if (p->cmds[0] && p->cmds[1])
		return ;
	if (p->cmds[0])
	{
		while (p->cmds[0]->cmd[i])
		{
			if (p->cmds[0]->cmd[i + 1] == NULL)
				val = ft_strdup(p->cmds[0]->cmd[i]);
			i++;
		}
	}
	if (!val)
		return ;
	mini_setenv("_", val, &p->env);
	free(val);
}

int	quotes_checker(char *str)
{
	int	s_flag;
	int	d_flag;
	int	i;

	s_flag = 0;
	d_flag = 0;
	i = ft_strlen(str);
	if (is_between_dquote(str, i))
		d_flag = 1;
	if (is_between_squote(str, i))
		s_flag = 1;
	if (s_flag == 1)
	{
		error_msg(NULL, 0, NULL,
			"unexpected EOF while looking for matching `\''");
		return (1);
	}
	if (d_flag == 1)
	{
		error_msg(NULL, 0, NULL,
			"unexpected EOF while looking for matching `\"'");
		return (1);
	}
	return (0);
}

int	is_invalid_last_token(t_token *token)
{
	if (token->type == TOKEN_REDIRAPP
		|| token->type == TOKEN_REDIRIN
		|| token->type == TOKEN_REDIROUT
		|| token->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	check_token(t_prompt *p)
{
	int	i;

	i = 0;
	if (p->tokens[0] && p->tokens[0]->type == TOKEN_PIPE)
	{
		err_msg_token(p->tokens[0]->value, p);
		return (0);
	}
	while (p->tokens[i])
	{
		if (p->tokens[i + 1] == NULL && p->tokens[i]->type == TOKEN_PIPE)
		{
			err_msg_token(p->tokens[i]->value, p);
			return (0);
		}
		if (p->tokens[i + 1] == NULL && is_invalid_last_token(p->tokens[i]))
		{
			err_msg_token(p->tokens[i]->value, p);
			return (0);
		}
		i++;
	}
	return (1);
}

void	parse_args(t_prompt *p, char *input)
{
	if (parse_args_sub1(input, p))
		return ;
	p->tokens = lexer(input, p);
	if (!p->tokens)
		return ;
	if ((p->tokens && !p->tokens[0]) || check_token(p) == 0)
	{
		free_tokens(p);
		return ;
	}
	expander(p->tokens, p);
	p->nb_cmd = get_cmds_nbr(p->tokens);
	p->cmds = parser(p);
	set_lastarg(p);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipeline(p);
	free_all2(p);
}
