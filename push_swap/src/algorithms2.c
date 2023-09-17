/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:14:04 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/19 15:45:17 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	find_min(t_stack *a)
{
	int	i;
	int	index;
	int	tmp;

	i = 1;
	index = 0;
	tmp = a->collection[0];
	while (i < a->size)
	{
		if (a->collection[i] < tmp)
		{
			index = i;
			tmp = a->collection[i];
		}
		i++;
	}
	return (index);
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	i;
	int	j;
	int	digits;

	i = a->size;
	j = 0;
	digits = find_digits(find_max(a));
	while (j < digits)
	{
		while (i > 0)
		{
			if (((a->collection[a->size - 1] >> j) & 0x01) == 0)
				pb(b, a);
			else
				ra(a);
			i--;
		}
		while (!is_empty(b))
			pa(a, b);
		j++;
		i = a->size;
	}
}

void	insertion_sort(int x[], int n)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	while (i < n)
	{
		k = x[i];
		j = i - 1;
		while (j >= 0 && x[j] > k)
		{
			x[j + 1] = x[j];
			j = j - 1;
		}
		x[j + 1] = k;
		i++;
	}
}

void	indexer(int u[], int s[], int res[], int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < n)
	{
		while (j < n)
		{
			if (u[j] == s[i])
			{
				res[j] = i;
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	few_numbers(int argc, t_stack *a, t_stack *b)
{
	if (argc == 3)
	{
		if (a->collection[0] < a->collection[1])
			ra(a);
	}
	else if (argc == 4)
		three_nums(a);
	else if (argc == 5)
		four_nums(a, b);
	else if (argc == 6)
		five_nums(a, b);
}
