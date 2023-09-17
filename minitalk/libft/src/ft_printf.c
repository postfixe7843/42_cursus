/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:46:20 by nlence-l          #+#    #+#             */
/*   Updated: 2023/03/03 17:28:47 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	if (format == NULL)
		return (0);
	len = 0;
	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_parser(args, format[++i]);
			i++;
		}
		else
			len += ft_print_char(format[i++]);
		if (len == -1)
			return (-1);
	}
	va_end(args);
	return (len);
}
