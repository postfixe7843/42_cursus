/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:23:23 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/19 15:20:59 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	free_arr(char ***res, int len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free((*res)[i]);
		i++;
	}
	free(*res);
	*res = NULL;
}

void	sort_it1(int n, t_stack *a, t_stack *b)
{
	if (n <= 5)
		few_numbers(n + 1, a, b);
	else
		radix_sort(a, b);
}

void	sort_it2(int n, t_stack *a, t_stack *b)
{
	if (n <= 6)
		few_numbers(n, a, b);
	else
		radix_sort(a, b);
}

void	create_indexed_array(int *sorted_arr, int *indexed_arr, t_stack *a)
{
	sorted_arr = malloc(sizeof(int) * a->size);
	indexed_arr = malloc(sizeof(int) * a->size);
	copy_arr(a->collection, sorted_arr, a->size);
	insertion_sort(sorted_arr, a->size);
	indexer(a->collection, sorted_arr, indexed_arr, a->size);
	copy_arr(indexed_arr, a->collection, a->size);
	free(sorted_arr);
	free(indexed_arr);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		*sorted_arr;
	int		*indexed_arr;
	char	**test;

	if (argc == 1)
		return (1);
	if (argc == 2)
	{
		a = make_a(argv);
		if (!a)
			return (1);
	}
	else
	{
		a = create_stack(argc - 1);
		if (check_stack2(argc - 1, argv, a) == 1)
			return (1);
	}
	b = create_stack(a->size);
	create_indexed_array(sorted_arr, indexed_arr, a);
	sorting_time(argc, count_words(argv[1]), a, b);
	destroy_stacks(a, b);
	return (0);
}
