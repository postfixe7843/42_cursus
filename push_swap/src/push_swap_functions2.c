/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_functions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:12:36 by nlence-l          #+#    #+#             */
/*   Updated: 2023/04/26 17:45:10 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	ra(t_stack *a)
{
	int	tmp;
	int	i;

	if (a->size == 0 || a->size == 1)
		return (1);
	i = a->size - 1;
	tmp = a->collection[a->size - 1];
	while (i > 0)
	{
		a->collection[i] = a->collection[i - 1];
		i--;
	}
	a->collection[0] = tmp;
	write(1, "ra\n", 3);
	return (0);
}

int	rb(t_stack *a)
{
	int	tmp;
	int	i;

	if (a->size == 0 || a->size == 1)
		return (1);
	i = a->size - 1;
	tmp = a->collection[a->size - 1];
	while (i > 0)
	{
		a->collection[i] = a->collection[i - 1];
		i--;
	}
	a->collection[0] = tmp;
	write(1, "rb\n", 3);
	return (0);
}

int	rr(t_stack *a, t_stack *b)
{
	if (!ra(a) || rb(b))
		return (1);
	write(1, "rr\n", 3);
	return (0);
}

int	rra(t_stack *a)
{
	int	tmp;
	int	i;

	if (a->size == 0 || a->size == 1)
		return (1);
	i = 1;
	tmp = a->collection[0];
	while (i < a->size)
	{
		a->collection[i - 1] = a->collection[i];
		i++;
	}
	a->collection[a->size - 1] = tmp;
	write(1, "rra\n", 4);
	return (0);
}

int	rrb(t_stack *a)
{
	int	i;
	int	tmp;

	if (a->size == 0 || a->size == 1)
		return (1);
	i = 1;
	tmp = a->collection[0];
	while (i < a->size)
	{
		a->collection[i - 1] = a->collection[i];
		i++;
	}
	a->collection[a->size - 1] = tmp;
	write(1, "rrb\n", 4);
	return (0);
}
