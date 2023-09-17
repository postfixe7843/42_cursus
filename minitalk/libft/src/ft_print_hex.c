/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:43:37 by nlence-l          #+#    #+#             */
/*   Updated: 2023/03/03 17:26:25 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_hex_len(unsigned	int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

int	ft_get_hex(unsigned int n, const char c)
{
	int	x;

	x = 0;
	if (n >= 16)
	{
		if (ft_get_hex(n / 16, c) == -1)
			return (-1);
		if (ft_get_hex(n % 16, c) == -1)
			return (-1);
	}
	else
	{
		if (n <= 9)
			x = ft_print_char(n + '0');
		else
		{
			if (c == 'x')
				x = ft_print_char(n - 10 + 'a');
			if (c == 'X')
				x = ft_print_char(n - 10 + 'A');
		}
		if (x == -1)
			return (-1);
	}
	return (ft_hex_len(n));
}

int	ft_print_hex(unsigned int n, const char c)
{
	if (n == 0)
		return (ft_print_char('0'));
	else
		return (ft_get_hex(n, c));
}
