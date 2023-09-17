/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:42:13 by nlence-l          #+#    #+#             */
/*   Updated: 2023/02/28 19:51:45 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_parser(va_list args, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_print_char(va_arg(args, int));
	else if (c == 's')
		len += ft_print_str(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		len += ft_print_nbr(va_arg(args, int));
	else if (c == 'u')
		len += ft_print_u(va_arg(args, unsigned int));
	else if (c == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long));
	else if (c == 'x' || c == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), c);
	else if (c == '%')
		len += ft_print_percent();
	return (len);
}
