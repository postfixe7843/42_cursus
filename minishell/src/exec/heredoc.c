/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:01:18 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 15:27:33 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_heredoc_name(void)
{
	static int	num;
	char		*number;
	char		*heredoc_filename;

	number = ft_itoa(num);
	if (!number)
		return (NULL);
	heredoc_filename = ft_strjoin("./.heredoc_", number);
	free(number);
	num++;
	return (heredoc_filename);
}

static void	remove_quotes(t_command *cmd)
{
	int		i;
	char	*new_value;
	int		open_squote;
	int		open_dquote;

	i = 0;
	new_value = ft_strdup(cmd->heredoc_delimiter);
	open_squote = 0;
	open_dquote = 0;
	while (new_value[i])
		check_quotes(new_value, &open_squote, &open_dquote, &i);
	free(cmd->heredoc_delimiter);
	cmd->heredoc_delimiter = new_value;
}

int	open_heredoc(t_command *cmd, t_prompt *p)
{
	int	ret;

	remove_quotes(cmd);
	cmd->in_file = create_heredoc_name();
	cmd->in_fd = open(cmd->in_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->in_fd == -1)
		error_msg("heredoc", 0, cmd->in_file, strerror(errno));
	ret = write_in_heredoc(cmd, p);
	if (ret)
		return (1);
	close(cmd->in_fd);
	return (ret);
}

int	heredoc(t_command *cmd, t_prompt *p)
{
	int	ret;

	ret = 0;
	if (cmd->heredoc_delimiter)
		ret = open_heredoc(cmd, p);
	if (ret)
		return (ret);
	if (cmd->in_file != NULL)
		cmd->in_fd = open(cmd->in_file, O_RDONLY);
	else
		cmd->in_fd = -1;
	if (cmd->in_fd == -1)
		error_msg("heredoc", 0, cmd->in_file, strerror(errno));
	return (ret);
}
