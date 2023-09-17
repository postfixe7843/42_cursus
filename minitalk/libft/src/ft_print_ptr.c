/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:09:35 by nlence-l          #+#    #+#             */
/*   Updated: 2023/03/01 14:11:05 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_ptr_len(unsigned long long n)
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

void	ft_get_ptr(unsigned long long n)
{
	if (n >= 16)
	{
		ft_get_ptr(n / 16);
		ft_get_ptr(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_print_char(n + '0');
		else
			ft_print_char(n - 10 + 'a');
	}
}

int	ft_print_ptr(unsigned long long n)
{
	int	len;

	len = 0;
	len += write(1, "0x", 2);
	if (len == -1)
		return (-1);
	if (n == 0)
	{
		len += write(1, "0", 1);
		if (len == -1)
			return (-1);
	}
	else
	{
		ft_get_ptr(n);
		len += ft_ptr_len(n);
	}
	return (len);
}
