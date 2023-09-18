/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:12:56 by jschmitt          #+#    #+#             */
/*   Updated: 2023/02/14 15:57:43 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	end_of_line(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*extract_line(char *buf)
{
	int		i;
	int		len_until_nl;
	char	*line;

	if (buf == NULL)
		return (NULL);
	i = 0;
	len_until_nl = len_until_char(buf, '\n') + 1;
	line = malloc(sizeof(char) * len_until_nl + 1);
	if (line == NULL)
		return (NULL);
	while (i < len_until_nl && buf[i] != '\0')
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	save_buf_remain(char *buf, char *to_save)
{
	int		i;
	int		j;

	i = len_until_char(buf, '\n') + 1;
	j = 0;
	if (i == BUFFER_SIZE)
		to_save[0] = 0;
	while (buf[i] != '\0')
	{
		to_save[j] = buf[i];
		i++;
		j++;
	}
	to_save[j] = '\0';
}

int	len_until_char(const char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s1_len;
	int		len_joined;
	char	*str_joined;

	i = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = len_until_char(s1, '\0');
	len_joined = s1_len + len_until_char(s2, '\0');
	str_joined = malloc(sizeof(char) * (len_joined + 1));
	if (str_joined == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		str_joined[i] = s1[i];
	i = -1;
	while (s2[++i] != '\0')
		str_joined[i + s1_len] = s2[i];
	str_joined[len_joined] = '\0';
	return (str_joined);
}
