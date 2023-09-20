/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:18:17 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/17 19:24:11 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_status = 0;

int	init_wd_oldwd(t_prompt *p)
{
	char	cwd[1024];
	char	*wd;
	char	*get_env;

	wd = getcwd(cwd, sizeof(cwd));
	p->wd = ft_strdup(wd);
	if (!p->wd)
		return (0);
	get_env = mini_getenv("OLDPWD", p->env);
	if (get_env)
		p->old_wd = get_env;
	else
	{
		p->old_wd = ft_strdup(wd);
		if (!p->old_wd)
			return (0);
	}
	return (1);
}

int	init_prompt(t_prompt *p, char **env)
{
	if (!env)
		return (0);
	p->env = env;
	p->last_pipeline_status = 0;
	if (!init_wd_oldwd(p))
		return (0);
	p->cmds = NULL;
	p->tokens = NULL;
	p->splitted_path = NULL;
	p->pid = -1;
	p->childs = NULL;
	p->pipes = NULL;
	p->nb_cmd = 0;
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char		**mini_env;
	char		*input;
	t_prompt	*p;

	(void)argc;
	(void)argv;
	mini_env = init_mini_envp(env);
	p = malloc(sizeof(t_prompt));
	if (!init_prompt(p, mini_env))
	{
		free_prompt(p);
		error_msg("fatal error", 0, "cannot initialize prompt",
			strerror(errno));
		return (1);
	}
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell > ");
		parse_args(p, input);
		free (input);
	}
	return (0);
}
