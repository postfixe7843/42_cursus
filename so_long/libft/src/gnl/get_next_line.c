/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:56:44 by nlence-l          #+#    #+#             */
/*   Updated: 2023/02/16 15:56:52 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_get_line(char *s1)
{
	int		i;
	char	*str;

	i = 0;
	if (!s1[i])
		return (NULL);
	while (s1[i] && s1[i] != '\n')
		i++;
	if (s1[i] == '\0')
		str = (char *)malloc(sizeof(char) * (i + 1));
	else
		str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		str[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_parse(char *s1)
{
	int		i;
	int		j;

	i = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	if (!s1[i] || s1[i] == '\0')
	{
		free(s1);
		return (NULL);
	}
	i++;
	j = 0;
	while (s1[i])
		s1[j++] = s1[i++];
	s1[j] = '\0';
	return (s1);
}

char	*ft_read(int fd, char *s1)
{
	char	*tmp;
	int		bytes;

	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(s1, '\n') && bytes != 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(tmp);
			free(s1);
			return (NULL);
		}
		tmp[bytes] = '\0';
		if (bytes != 0)
			s1 = ft_strjoin(s1, tmp);
	}
	free(tmp);
	return (s1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = ft_get_line(buffer);
	buffer = ft_parse(buffer);
	return (line);
}
