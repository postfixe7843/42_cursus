/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:45:06 by nlence-l          #+#    #+#             */
/*   Updated: 2023/03/03 17:27:45 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_print_str(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		x = write(1, &str[i++], 1);
		if (x == -1)
			return (-1);
	}
	return (i);
}