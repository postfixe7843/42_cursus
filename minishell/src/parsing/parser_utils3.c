/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:55:27 by nlence-l          #+#    #+#             */
/*   Updated: 2023/09/19 18:35:55 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirout_is_first(t_token **tokens, int i)
{
	if (i == 0)
		return (1);
	else if (i > 0 && tokens[i - 1]->type == TOKEN_PIPE)
		return (1);
	return (0);
}

int	get_cmd_len(t_token **tokens, int i)
{
	int	len;
	int	j;

	len = 0;
	j = 0;
	while (tokens[i] && (tokens[i]->type != TOKEN_PIPE))
	{
		if (tokens[i]->type == TOKEN_REDIROUT || tokens[i]->type
			== TOKEN_REDIRAPP || tokens[i]->type == TOKEN_REDIRIN)
		{
			i += 2;
			continue ;
		}
		else if (tokens[i]->type == TOKEN_EXPANDED)
		{
			while (tokens[i]->value[j++])
			{
				if (tokens[i]->value[j] == ' ')
					len++;
			}
		}
		len++;
		i++;
	}
	return (len);
}

int	get_cmds_nbr(t_token **tokens)
{
	int	i;
	int	tokens_nbr;

	i = 0;
	tokens_nbr = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_PIPE)
			tokens_nbr++;
		i++;
	}
	return (tokens_nbr + 1);
}

void	init_cmd(t_command *cmd)
{
	cmd->cmd = NULL;
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->heredoc_expand = 1;
	cmd->append = 0;
	cmd->stdin_saved = -1;
	cmd->stdout_saved = -1;
	cmd->in_fd = -1;
	cmd->out_fd = -1;
}
