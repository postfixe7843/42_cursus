/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:16:13 by nlence-l          #+#    #+#             */
/*   Updated: 2023/06/29 18:16:15 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	ft_map_height(t_data *info)
{
	char		*line;
	int			fd;

	fd = open(info->name, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error.\n", 7);
		write(2, "Map doesn't exist!\n", 19);
		ft_exit(info);
	}
	line = get_next_line(fd);
	if (!line)
		exit (EXIT_FAILURE);
	while (line[info->width] != '\0' && line[info->width] != '\n')
		info->width++;
	while (line)
	{
		info->height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	line = NULL;
	close(fd);
}

void	ft_read_map(t_data *info)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(info->name, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error.\n", 7);
		write(2, "Map doesn't exist!\n", 19);
		ft_exit(info);
	}
	line = get_next_line(fd);
	info->map = (char **)malloc(sizeof(char *) * (info->height + 1));
	i = 0;
	while (line)
	{
		if (i != (info->height - 1))
			line[(int)ft_strlen(line) - 1] = '\0';
		info->map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	info->map[i] = NULL;
	free(line);
	close(fd);
}
