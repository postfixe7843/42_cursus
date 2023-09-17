/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:13:11 by nlence-l          #+#    #+#             */
/*   Updated: 2023/04/26 16:17:13 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

t_stack	*create_stack(int capacity)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	if (capacity <= 0)
		return (NULL);
	stack->collection = malloc(sizeof(int) * capacity);
	if (!stack->collection)
	{
		free(stack);
		return (NULL);
	}
	stack->capacity = capacity;
	stack->size = 0;
	return (stack);
}

void	destroy_stack(t_stack *stack)
{
	free(stack->collection);
	free(stack);
}

int	is_empty(t_stack *stack)
{
	return (stack->size == 0);
}

int	push(t_stack *stack, int item)
{
	if (is_full(stack))
		return (1);
	stack->collection[stack->size] = item;
	stack->size++;
	return (0);
}

int	is_full(t_stack *stack)
{
	return (stack->size == stack->capacity);
}
