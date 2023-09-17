/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:13:50 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/19 15:44:43 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	three_nums(t_stack *stack)
{
	if (stack->collection[0] > stack->collection[1] \
			&& stack->collection[2] > stack->collection[1] \
			&& stack->collection[2] > stack->collection[0])
		ra(stack);
	else if (stack->collection[2] > stack->collection[1] \
			&& stack->collection[0] > stack->collection[1])
		sa(stack);
	else if (stack->collection[0] < stack->collection[1] \
			&& stack->collection[2] < stack->collection[1] \
			&& stack->collection[0] < stack->collection[2])
		rra(stack);
	else if (stack->collection[0] < stack->collection[1] \
			&& stack->collection[2] < stack->collection[1])
	{
		sa(stack);
		ra(stack);
	}
	else if (stack->collection[0] < stack->collection[1] \
			&& stack->collection[2] > stack->collection[1])
	{
		ra(stack);
		sa(stack);
	}
}

void	four_nums(t_stack *a, t_stack *b)
{
	pb(b, a);
	three_nums(a);
	if (b->collection[0] < a->collection[2])
		pa(a, b);
	else if (b->collection[0] > a->collection[0])
	{
		pa(a, b);
		ra(a);
	}
	else if (b->collection[0] > a->collection[2] \
			&& b->collection[0] < a->collection[1])
	{
		pa(a, b);
		sa(a);
	}
	else if (b->collection[0] > a->collection[1] \
			&& b->collection[0] < a->collection[0])
	{
		pa(a, b);
		rra(a);
		sa(a);
		ra(a);
		ra(a);
	}
}

void	five_nums1(t_stack *a, t_stack *b, int index)
{
	if (index == 0)
	{
		rra(a);
		pb(b, a);
	}
	else if (index == 1)
	{
		rra(a);
		rra(a);
		pb(b, a);
	}
	else if (index == 2)
	{
		ra(a);
		sa(a);
		pb(b, a);
	}
	else if (index == 3)
	{
		sa(a);
		pb(b, a);
	}
	else if (index == 4)
		pb(b, a);
}

void	five_nums2(t_stack *a, t_stack *b, int index)
{
	if (index == 0)
	{
		rra(a);
		pb(b, a);
	}
	else if (index == 1)
	{
		rra(a);
		rra(a);
		pb(b, a);
	}
	else if (index == 2)
	{
		sa(a);
		pb(b, a);
	}
	else if (index == 3)
		pb(b, a);
}

void	five_nums(t_stack *a, t_stack *b)
{
	int	index;

	index = find_min(a);
	five_nums1(a, b, index);
	index = find_min(a);
	five_nums2(a, b, index);
	three_nums(a);
	pa(a, b);
	pa(a, b);
}
