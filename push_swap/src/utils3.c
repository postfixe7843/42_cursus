/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:54:21 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/19 15:54:43 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	free_arr2(int **a, int **b)
{
	free(a);
	free(b);
}

void	sorting_time(int argc, int len, t_stack *a, t_stack *b)
{
	if (argc == 2)
		sort_it1(len, a, b);
	else
		sort_it2(argc, a, b);
}

int	count_words(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
	}
	return (wc);
}

int	check_empty(char **argv)
{
	if (argv[1][0] == '\0')
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}

void	destroy_stacks(t_stack *a, t_stack *b)
{
	destroy_stack(a);
	destroy_stack(b);
}
