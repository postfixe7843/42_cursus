/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:55:02 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/19 18:35:01 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_commands(t_prompt *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (p->cmds)
	{
		while (p->cmds[i])
		{
			while (p->cmds[i]->cmd[j])
			{
				free(p->cmds[i]->cmd[j]);
				j++;
			}
			free_command(p->cmds[i]);
			i++;
			j = 0;
		}
		free(p->cmds);
		p->cmds = NULL;
	}
}

void	free_tokens(t_prompt *p)
{
	int	i;

	i = 0;
	if (p->tokens)
	{
		while (p->tokens[i])
		{
			if (p->tokens[i]->type == TOKEN_EXPANDED
				|| p->tokens[i]->type == TOKEN_PIPE
				|| p->tokens[i]->type == TOKEN_REDIRAPP
				|| p->tokens[i]->type == TOKEN_REDIRIN
				|| p->tokens[i]->type == TOKEN_REDIROUT
				|| p->tokens[i]->type == TOKEN_HEREDOC
				|| p->tokens[i]->type == TOKEN_FILE)
				free(p->tokens[i]->value);
			free(p->tokens[i]->str_input);
			free(p->tokens[i]);
			i++;
		}
		free(p->tokens);
		p->tokens = NULL;
	}
}

void	free_environment(t_prompt *p)
{
	int	i;

	i = 0;
	if (p->env)
	{
		while (p->env[i])
		{
			free(p->env[i]);
			i++;
		}
		free(p->env);
		p->env = NULL;
	}
}

void	free_splitted_path(t_prompt *p)
{
	int	i;

	i = 0;
	if (p->splitted_path)
	{
		while (p->splitted_path[i])
		{
			free(p->splitted_path[i]);
			i++;
		}
		free(p->splitted_path);
		p->splitted_path = NULL;
	}
}

void	free_prompt(t_prompt *p)
{
	if (p)
	{
		free_splitted_path(p);
		free_environment(p);
		free_tokens(p);
		free_commands(p);
		if (p->wd)
			free(p->wd);
		if (p->old_wd)
			free(p->old_wd);
		free(p);
		p = NULL;
	}
}
