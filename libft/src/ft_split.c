/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:39:37 by nlence-l          #+#    #+#             */
/*   Updated: 2022/12/13 19:26:58 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
				s++;
			words++;
			continue ;
		}
		s++;
	}
	return (words);
}

static const char	*ft_make(char **dest, const char *src, char c)
{
	size_t	len;
	size_t	i;

	while (*src == c)
		src++;
	len = 0;
	while (src[len] != '\0' && src[len] != c)
		len++;
	*dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!*dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		(*dest)[i] = src[i];
		i++;
	}
	(*dest)[i] = '\0';
	src += len + 1;
	return (src);
}

static void	free_res(char ***res, size_t len)
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

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	words;
	size_t	i;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res[words] = NULL;
	i = 0;
	while (i < words)
	{
		s = ft_make(res + i, s, c);
		if (s == NULL)
		{
			free_res(&res, i);
			break ;
		}
		i++;
	}
	return (res);
}
