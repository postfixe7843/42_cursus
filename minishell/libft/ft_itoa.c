/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:11:10 by jschmitt          #+#    #+#             */
/*   Updated: 2022/11/07 14:46:40 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoalen(int n);
static int	ft_abs(int n);

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		size;

	size = ft_itoalen(n);
	i = size - 1;
	s = malloc(sizeof(char) * (size + 1));
	if (s == NULL)
		return (NULL);
	if (n < 0)
		s[0] = '-';
	if (n == 0)
		s[0] = '0';
	while (n != 0)
	{
		s[i] = (ft_abs(n % 10)) + '0';
		n = n / 10;
		i--;
	}
	s[size] = '\0';
	return (s);
}

static int	ft_itoalen(int n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		else
		{
			n = ft_abs(n);
			len ++;
		}
	}
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}
