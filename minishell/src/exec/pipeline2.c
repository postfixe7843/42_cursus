/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:41:12 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/17 20:38:48 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

void	append_backslash(char **splitted_path)
{
	int		i;
	int		num_strings;
	int		new_len;
	char	*new_string;

	i = 0;
	num_strings = 0;
	new_len = 0;
	while (splitted_path[num_strings])
		num_strings++;
	while (i < num_strings)
	{
		new_len = ft_strlen(splitted_path[i]) + 1;
		new_string = (char *)malloc(sizeof(char) * (new_len + 1));
		ft_strcpy(new_string, splitted_path[i]);
		new_string[new_len - 1] = '/';
		new_string[new_len] = '\0';
		free(splitted_path[i]);
		splitted_path[i] = new_string;
		i++;
	}
}

int	get_cmds_nbr2(t_command **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

int	is_dir(t_prompt *p, char *str)
{
	struct stat	str_stat;
	char		*dir;
	int			flag;

	flag = 0;
	if (ft_strchr(str, '/') && stat(str, &str_stat) == 0)
		return (S_ISDIR(str_stat.st_mode));
	else if (!p->splitted_path)
	{
		if (!ft_strchr(str, '/'))
		{
			flag = 1;
			dir = ft_strdup("./");
			dir = join_msg(dir, str);
		}
		if (stat(dir, &str_stat) == 0)
			return (S_ISDIR(str_stat.st_mode));
	}
	if (flag)
		free (dir);
	return (0);
}

void	check_cmd_not_found(char *path)
{
	if (!ft_strchr(path, '/'))
	{
		error_msg(NULL, 0, path, "command not found");
		exit(127);
	}
	if (access(path, X_OK) == 0)
	{
		error_msg(NULL, 0, path, strerror(errno));
		exit(126);
	}
	if (access(path, F_OK) == 0 && access(path, R_OK) != 0)
	{
		error_msg(NULL, 0, path, strerror(errno));
		exit(126);
	}
	if (access(path, R_OK) == 0 && access(path, X_OK) != 0)
	{
		error_msg(NULL, 0, path, strerror(errno));
		exit(126);
	}
	else
	{
		error_msg(NULL, 0, path, strerror(errno));
		exit(127);
	}
}
