/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:14:34 by jschmitt          #+#    #+#             */
/*   Updated: 2022/11/02 17:19:54 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		mod;
	char	c;

	mod = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return ;
		}
		else
		{
			c = '-';
			ft_putchar_fd(c, fd);
			n = n * -1;
		}
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	mod = n % 10;
	c = mod + 48;
	ft_putchar_fd(c, fd);
}
