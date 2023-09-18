/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 10:40:30 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/16 10:47:34 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*error_null(char *cmd, int quote, char *input, char *err_msg)
{
	error_msg(cmd, quote, input, err_msg);
	return (NULL);
}

int	error_ret(char *cmd, char *input, char *err_msg, int ret)
{
	error_msg(cmd, 1, input, err_msg);
	return (ret);
}

void	error_malloc_void(void)
{
	error_msg("malloc", 0, NULL, "memory allocation failed");
}

void	*error_malloc_null(void)
{
	error_malloc_void();
	return (NULL);
}
