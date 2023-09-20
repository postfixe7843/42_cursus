/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:34:43 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/20 13:08:16 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_command(t_command *cmd)
{
	close_fds(cmd, 0);
	close_fds(cmd, 1);
	reset_fds(cmd);
	clean_old_file(cmd, 0);
	clean_old_file(cmd, 1);
	clean_old_heredoc(cmd);
	free(cmd->cmd);
	free(cmd->in_file);
	free(cmd->out_file);
	free(cmd->heredoc_delimiter);
	free(cmd);
}
