/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:44:05 by nlence-l          #+#    #+#             */
/*   Updated: 2023/02/28 19:52:56 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_nbrlen(int n)
{
	int	res;

	res = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		res *= 10;
	}
	return (res);
}

int	ft_print_nbr(int n)
{
	int	len;
	int	res;

	len = ft_nbrlen(n);
	res = 0;
	if (n == -2147483648)
		return (res += ft_print_str("-2147483648"));
	if (n < 0 && n != -2147483648)
	{
		res += ft_print_char('-');
		if (res == -1)
			return (-1);
		n = n * (-1);
	}
	while (len != 0)
	{
		res += ft_print_char(n / len + '0');
		if (res == -1)
			return (-1);
		n = n % len;
		len = len / 10;
	}
	return (res);
}
