/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:08:40 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/07 16:13:14 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	*s_endl;

	if (s == NULL)
		return ;
	s_endl = ft_strjoin(s, "\n");
	if (!s_endl)
		return ;
	ft_putstr_fd(s_endl, fd);
	free(s_endl);
}
