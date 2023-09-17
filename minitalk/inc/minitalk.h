/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:19:22 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/18 15:22:55 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>

void	ft_handler(int signal);
void	ft_sender(int pid, char c);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
char	*add_c_to_str(char *str, char c);
char	*print_and_free(char *str);

#endif
