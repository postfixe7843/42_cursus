/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:08:47 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/19 15:40:59 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int	*collection;
	int	capacity;
	int	size;
}	t_stack;

/* - - - - - STACK FUNCTIONS - - - - - */

t_stack			*create_stack(int capacity);
void			destroy_stack(t_stack *stack);
int				is_empty(t_stack *stack);
int				push(t_stack *stack, int item);
int				is_full(t_stack *stack);

/* - - - - - PUSH_SWAP'S FUNCTIONS - - - - - */

int				sa(t_stack *a);
int				sb(t_stack *a);
int				ss(t_stack *a, t_stack *b);
int				pa(t_stack *a, t_stack *b);
int				pb(t_stack *a, t_stack *b);
int				ra(t_stack *a);
int				rb(t_stack *a);
int				rr(t_stack *a, t_stack *b);
int				rra(t_stack *a);
int				rrb(t_stack *a);
int				rrr(t_stack *a, t_stack *b);

/* - - - - - - - - PROJECT'S FUNCTIONS - - - - - - - */

int				is_integer(char *nbr);
int				ft_atoi(char *str);
void			three_nums(t_stack *stack);
void			five_nums1(t_stack *a, t_stack *b, int index);
void			five_nums(t_stack *a, t_stack *b);
void			five_nums2(t_stack *a, t_stack *b, int index);
void			radix_sort(t_stack *a, t_stack *b);
void			insertion_sort(int x[], int n);
void			four_nums(t_stack *a, t_stack *b);
void			few_numbers(int argc, t_stack *a, t_stack *b);
int				find_max(t_stack *stack);
int				find_digits(int n);
void			indexer(int u[], int s[], int res[], int n);
int				check_stack1(int n, char **tab, t_stack *a);
int				check_stack2(int n, char **tab, t_stack *a);
int				push_into_a1(int n, char **tab, t_stack *a);
int				push_into_a2(int n, char **tab, t_stack *a);
int				check_duplicates(t_stack *a);
int				check_sort(t_stack *a);
void			copy_arr(int *arr1, int *arr2, int n);
long long		check_min_max(char *str);
void			sort_it1(int n, t_stack *a, t_stack *b);
void			sort_it2(int n, t_stack *a, t_stack *b);
int				find_min(t_stack *a);
void			free_arr(char ***res, int len);
char			**ft_split(char *str);
int				check_empty(char **argv);
t_stack			*make_a(char **argv);
void			destroy_stacks(t_stack *a, t_stack *b);
void			sorting_time(int argc, int len, t_stack *a, t_stack *b);
int				count_words(char *str);
int				is_space(char *str);
int				ft_strlen(char *str);
#endif
