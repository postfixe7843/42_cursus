/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:03:49 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/17 12:12:52 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_special_path(t_prompt *p, t_command *cmd, char *path, int *ret)
{
	char	*new_path;
	int		go_back;

	new_path = NULL;
	go_back = 0;
	if (path == NULL
		|| (ft_strcmp(path, "~") == 0 || ft_strcmp(path, "~/") == 0))
		new_path = mini_getenv("HOME", p->env);
	else if (path != NULL && path[0] == '-' && path[1] == '\0')
	{
		new_path = mini_getenv("OLDPWD", p->env);
		go_back = 1;
	}
	else
		return (0);
	if (new_path == NULL)
		return (0);
	*ret = mini_cd(p, cmd, new_path);
	free(new_path);
	if (go_back && *ret == 0)
		mini_pwd(p, cmd);
	return (1);
}

void	update_wd(t_prompt *p, char *new_pwd)
{
	mini_setenv("OLDPWD", p->wd, &(p->env));
	mini_setenv("PWD", new_pwd, &(p->env));
	if (p->old_wd)
		free(p->old_wd);
	p->old_wd = ft_strdup(p->wd);
	if (p->wd)
		free(p->wd);
	p->wd = ft_strdup(new_pwd);
	if (new_pwd)
		free(new_pwd);
}

int	mini_chdir(char *path, t_prompt *p)
{
	char	cwd[1024];
	char	*wd;
	char	*newpwd;

	wd = getcwd(cwd, sizeof(cwd));
	if ((!wd && chdir(path) != 0 && getcwd(cwd, sizeof(cwd)) == NULL)
		|| (wd && chdir(path) != 0))
	{
		error_msg("cd", 0, path, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (!wd && ft_strcmp(path, "..") == 0)
		chdir(p->old_wd);
	newpwd = getcwd(cwd, sizeof(cwd));
	if (newpwd)
		newpwd = ft_strdup(cwd);
	if (ft_strcmp(path, "//") == 0 && ft_strcmp(newpwd, "/") == 0)
		newpwd = join_msg(newpwd, "/");
	update_wd(p, newpwd);
	return (EXIT_SUCCESS);
}

int	check_special_path(t_prompt *p, char *path)
{
	char	*home;
	char	*oldpwd;

	home = mini_getenv("HOME", p->env);
	if (!home
		&& (!path || (path[0] == '~' && path[1] == '\0')))
	{
		error_msg("cd", 0, NULL, "HOME not set");
		return (1);
	}
	free(home);
	oldpwd = mini_getenv("OLDPWD", p->env);
	if (!oldpwd
		&& path != NULL && path[0] == '-' && path[1] == '\0')
	{
		error_msg("cd", 0, NULL, "OLDPWD not set");
		return (1);
	}
	free(oldpwd);
	return (0);
}

int	mini_cd(t_prompt *p, t_command *cmd, char *path)
{
	int		ret;

	ret = EXIT_SUCCESS;
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		error_msg("cd", 0, NULL, "too many arguments");
		return (1);
	}
	if (check_special_path(p, path))
		return (1);
	if (is_special_path(p, cmd, path, &ret))
		return (ret);
	if (path && path[0] == '\0')
		return (ret);
	ret = mini_chdir(path, p);
	return (ret);
}
