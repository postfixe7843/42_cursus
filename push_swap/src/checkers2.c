/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:50:12 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/19 15:50:17 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	push_into_a1(int n, char **tab, t_stack *a)
{
	int	x;

	x = n - 1;
	while (x >= 0)
	{
		if (check_min_max(tab[x]) > 2147483647 || \
				check_min_max(tab[x]) < -2147483648)
			return (1);
		if (is_integer(tab[x]) == 1)
			return (1);
		if (tab[x][0] == '\0')
			return (1);
		push(a, ft_atoi(tab[x]));
		x--;
	}
	return (0);
}

int	push_into_a2(int n, char **tab, t_stack *a)
{
	int	x;

	x = n;
	while (x > 0)
	{
		if (check_min_max(tab[x]) > 2147483647 || \
				check_min_max(tab[x]) < -2147483648)
			return (1);
		if (is_integer(tab[x]) == 1)
			return (1);
		if (tab[x][0] == '\0')
			return (1);
		push(a, ft_atoi(tab[x]));
		x--;
	}
	return (0);
}
