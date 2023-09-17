/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:19:57 by nlence-l          #+#    #+#             */
/*   Updated: 2023/05/18 16:21:38 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include "../libft/inc/libft.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*add_c_to_str(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	if (!str)
	{
		new = (char *)malloc(sizeof(char) * 2);
		if (!new)
			return (NULL);
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	free(str);
	return (new);
}

char	*print_and_free(char *str)
{
	if (str)
		ft_printf("%s\n", str);
	free(str);
	return (NULL);
}

void	ft_handler(int signal)
{
	static int	i;
	static char	c;
	static char	*str = NULL;

	if (signal == SIGUSR1)
		c = c | (0x01 << i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			str = print_and_free(str);
		}
		else
		{
			str = add_c_to_str(str, c);
		}
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	signal(SIGUSR1, &ft_handler);
	signal(SIGUSR2, &ft_handler);
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
