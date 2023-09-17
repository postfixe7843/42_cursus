/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:57:56 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/19 15:50:57 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	is_integer(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i] != '\0')
	{
		while (nbr[i] == '\t' || nbr[i] == ' ')
			i++;
		if (nbr[i] == '-')
			i++;
		if (nbr[i] < 48 || nbr[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
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

int	find_digits(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i++;
		n >>= 1;
	}
	return (i);
}

int	find_max(t_stack *stack)
{
	int				i;
	long long int	max;
	long long int	min;

	i = 0;
	max = stack->collection[i++];
	while (i < stack->size)
	{
		if (stack->collection[i] > max)
			max = stack->collection[i];
		i++;
	}
	i = 0;
	min = stack->collection[i];
	while (i < stack->size)
	{
		if (stack->collection[i] < min)
			min = stack->collection[i];
		i++;
	}
	if (min < 0)
		min = min * -1;
	if (min > max)
		max = min;
	return (max);
}

void	copy_arr(int *arr1, int *arr2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		arr2[i] = arr1[i];
		i++;
	}
}
