/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:26:41 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/14 13:28:14 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_prompt(t_prompt *p)
{
	char	*res;
	char	*user;
	char	cwd[1024];
	int		len;

	getcwd(cwd, sizeof(cwd));
	len = ft_strlen(mini_getenv("USER", p->env)) + 1;
	user = malloc(sizeof(char) * len);
	user = mini_getenv("USER", p->env);
	user = ft_strjoin(GREEN, user);
	user = ft_strjoin(user, "@minishell");
	user = ft_strjoin(user, DEFAULT);
	user = ft_strjoin(user, ":");
	user = ft_strjoin(user, MAGENTA);
	res = ft_strdup(cwd);
	res = ft_strjoin(cwd, DEFAULT);
	res = ft_strjoin(user, res);
	res = ft_strjoin(res, "$");
	return (res);
}
