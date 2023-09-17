/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_functions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:12:20 by nlence-l          #+#    #+#             */
/*   Updated: 2023/04/26 17:54:59 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	sa(t_stack *a)
{
	int	tmp;

	tmp = a->collection[a->size - 1];
	if (is_empty(a) || a->size == 1)
		return (1);
	a->collection[a->size - 1] = a->collection[a->size - 2];
	a->collection[a->size - 2] = tmp;
	write(1, "sa\n", 3);
	return (0);
}

int	sb(t_stack *a)
{
	int	tmp;

	tmp = a->collection[a->size - 1];
	if (is_empty(a) || a->size == 1)
		return (1);
	a->collection[a->size - 1] = a->collection[a->size - 2];
	a->collection[a->size - 2] = tmp;
	write(1, "sb\n", 3);
	return (0);
}

int	ss(t_stack *a, t_stack *b)
{
	if (!sa(a) || !sb(b))
		return (1);
	return (0);
}

int	pa(t_stack *a, t_stack *b)
{
	if (is_empty(b))
		return (1);
	a->size++;
	a->collection[a->size - 1] = b->collection[b->size - 1];
	b->size--;
	write(1, "pa\n", 3);
	return (0);
}

int	pb(t_stack *a, t_stack *b)
{
	if (is_empty(b))
		return (1);
	a->size++;
	a->collection[a->size - 1] = b->collection[b->size - 1];
	b->size--;
	write(1, "pb\n", 3);
	return (0);
}
