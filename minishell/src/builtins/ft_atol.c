/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:05:25 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/01 18:28:26 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_isspace(char c);

int	is_neg(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				return (-1);
			i++;
		}
		i++;
	}
	return (1);
}

int	out_limits(const char *str, unsigned long nb)
{
	if ((nb > LONG_MAX && is_neg(str) == 1)
		|| (nb > -(unsigned long)LONG_MIN && is_neg(str) == -1))
		return (1);
	return (0);
}

int	ft_atol_checker(const char *str, int *error)
{
	int				i;
	unsigned long	nb;
	unsigned long	last_nb;

	i = 0;
	nb = 0;
	last_nb = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		if (nb < last_nb || out_limits(str, nb))
			return (0);
		i++;
		last_nb = nb;
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		*error = 0;
	return (nb * is_neg(str));
}

static int	ft_isspace(char c)
{
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}
