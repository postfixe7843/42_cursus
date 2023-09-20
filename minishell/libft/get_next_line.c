/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:12:42 by jschmitt          #+#    #+#             */
/*   Updated: 2023/02/14 15:57:39 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char		reading_lines[FD_LIMIT][BUFFER_SIZE + 1];
	char			buf[BUFFER_SIZE + 1];
	char			*next_line;

	if (fd < 0 || fd >= FD_LIMIT || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (error_clean(reading_lines[fd], fd));
	next_line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (next_line == NULL)
		return (error_clean(reading_lines[fd], fd));
	next_line[0] = 0;
	if (reading_lines[fd][0] != 0)
	{
		next_line = find_line(reading_lines[fd], reading_lines[fd], next_line);
		if (end_of_line(next_line) == 1)
			return (return_line(reading_lines[fd], next_line));
	}
	next_line = read_line(fd, buf, reading_lines[fd], next_line);
	if (next_line == NULL || next_line[0] == 0)
	{
		free(next_line);
		return (error_clean(reading_lines[fd], fd));
	}
	return (next_line);
}

char	*find_line(char *buf, char *reading_line, char *next_line)
{
	char	*tmp;
	char	*tmp2;

	tmp = extract_line(buf);
	if (tmp == NULL)
	{
		reading_line[0] = 0;
		free(next_line);
		next_line = NULL;
		return (NULL);
	}
	tmp2 = next_line;
	next_line = gnl_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	if (next_line == NULL)
	{
		reading_line[0] = 0;
		return (NULL);
	}
	return (next_line);
}

char	*read_line(int fd, char *buf, char *reading_line, char *next_line)
{
	int		check_read;

	check_read = read(fd, buf, BUFFER_SIZE);
	buf[check_read] = '\0';
	while (end_of_line(buf) == 0 && check_read == BUFFER_SIZE)
	{
		next_line = find_line(buf, reading_line, next_line);
		check_read = read(fd, buf, BUFFER_SIZE);
		buf[check_read] = '\0';
	}
	next_line = find_line(buf, reading_line, next_line);
	if (end_of_line(buf) == 1 && check_read > 0)
		save_buf_remain(buf, reading_line);
	if ((end_of_line(buf) == 0 && check_read < BUFFER_SIZE) || check_read == 0)
		reading_line[0] = 0;
	return (next_line);
}

char	*return_line(char *reading_line, char *next_line)
{
	save_buf_remain(reading_line, reading_line);
	return (next_line);
}

void	*error_clean(char *reading_line, int fd)
{
	if (fd >= 0 && fd < FD_LIMIT)
		reading_line[0] = 0;
	return (NULL);
}
