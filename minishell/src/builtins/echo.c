/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:27:59 by jschmitt          #+#    #+#             */
/*   Updated: 2023/08/29 15:23:03 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	only_n(char *arg)
{
	int	i;
	int	only_n;

	i = 1;
	only_n = 0;
	while (arg[i])
	{
		if (arg[i] == 'n')
			only_n = 1;
		else
			return (0);
		i++;
	}
	return (only_n);
}

static int	no_new_line(char **argv)
{
	int	i;
	int	no_new_line;

	i = 0;
	no_new_line = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "-", 1) == 0
			&& only_n(argv[i]))
		{
			no_new_line = 1;
			i++;
		}
		else
			return (no_new_line);
	}
	return (no_new_line);
}

static int	index_str(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "-", 1) == 0
			&& only_n(argv[i]))
			i++;
		else
			break ;
	}
	if (!argv[i])
		return (-1);
	return (i);
}

static void	echo(char **argv)
{
	int	i;

	i = index_str(argv);
	if (i == -1)
		return ;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	mini_echo(t_command *cmd)
{
	int	no_nl;

	no_nl = no_new_line(&cmd->cmd[1]);
	echo(&cmd->cmd[1]);
	if (no_nl == 0)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
