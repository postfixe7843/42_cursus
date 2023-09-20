/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:29:38 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/16 15:14:50 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_args_sub1(char *input, t_prompt *p)
{
	if (!input)
		mini_exit(p, NULL);
	if (ft_strlen(input) > 0)
		add_history(input);
	if (quotes_checker(input))
	{
		error_msg(NULL, 0, NULL, "syntax error: unexpected end of file");
		return (1);
	}
	if (input[0] == '\0')
		return (1);
	return (0);
}

void	free_all2(t_prompt *p)
{
	free_commands(p);
	free_tokens(p);
	free_splitted_path(p);
	free_pipes_and_childs(p);
}
