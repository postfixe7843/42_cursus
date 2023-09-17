/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:59:47 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/19 15:49:53 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	check_duplicates(t_stack *a)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < a->size)
	{
		while (j < a->size)
		{
			if (a->collection[i] == a->collection[j])
				return (1);
			j++;
		}
		i++;
		j = i + 1;
	}
	return (0);
}

int	check_sort(t_stack *a)
{
	int	i;

	i = 0;
	while (i < (a->size))
	{
		if (a->collection[i] < a->collection[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int	check_stack1(int n, char **tab, t_stack *a)
{
	if (check_min_max(tab[0]) > 2147483647 || \
				check_min_max(tab[0]) < -2147483648)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (n == 1 && (is_integer(tab[0]) == 0))
		return (1);
	if (push_into_a1(n, tab, a) == 1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (check_duplicates(a) == 1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (check_sort(a) == 0)
		return (1);
	return (0);
}

int	check_stack2(int n, char **tab, t_stack *a)
{
	if (n == 1 && (is_integer(tab[1]) == 0))
		return (1);
	if (push_into_a2(n, tab, a) == 1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (check_duplicates(a) == 1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (check_sort(a) == 0)
		return (1);
	return (0);
}

long long	check_min_max(char *str)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	if (ft_strlen(str) > 30)
		return (3000000000);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (sign * res);
}
