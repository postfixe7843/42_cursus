/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:44:53 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/14 19:42:35 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c);
static int	ft_ifnegative(int is_negative, int nb);

int	ft_atoi(const char *str)
{
	int	i;
	int	is_negative;
	int	nb;

	i = 0;
	is_negative = 0;
	nb = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				is_negative = 1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			nb = (nb * 10) + (str[i] - 48);
			i++;
		}
		return (ft_ifnegative(is_negative, nb));
	}
	return (0);
}

static int	ft_ifnegative(int is_negative, int nb)
{
	if (is_negative == 1)
		nb = nb * -1;
	return (nb);
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
