/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:21:34 by jschmitt          #+#    #+#             */
/*   Updated: 2022/11/02 13:09:13 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*p;

	i = 0;
	uc = (unsigned char)c;
	p = (unsigned char *)s;
	while (i < n)
	{
		if (p[i] == uc)
			return ((void *)&p[i]);
		i++;
	}
	return (0);
}
