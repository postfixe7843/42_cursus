/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:28:08 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/18 15:28:12 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);
int		ft_parser(va_list args, char c);
int		ft_print_char(const char c);
int		ft_print_hex(unsigned int n, const char c);
int		ft_get_hex(unsigned int n, const char c);
int		ft_hex_len(unsigned	int n);
int		ft_print_nbr(int n);
int		ft_nbrlen(int n);
int		ft_print_percent(void);
int		ft_print_str(char *str);
int		ft_print_u(unsigned int n);
int		ft_print_ptr(unsigned long long n);
void	ft_get_ptr(unsigned long long n);
int		ft_ptr_len(unsigned long long n);
int		ft_ulen(unsigned int n);

#endif
