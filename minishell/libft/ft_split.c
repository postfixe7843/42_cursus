/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:42:34 by jschmitt          #+#    #+#             */
/*   Updated: 2023/03/29 21:35:38 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_len_beforesep(char const *str, char sep);
static int		ft_strs_count(char const *str, char sep);
static char		*ft_strcpy_untilsep(char *dest, char const *src, char sep);
static int		ft_split_it(int i, char const *s, char c, char **ssplit);

char	**ft_split(char const *s, char c)
{
	char	**ssplit;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	ssplit = malloc(sizeof(char **) * ((ft_strs_count(s, c) + 1)));
	if (ssplit == NULL)
		return (NULL);
	i = ft_split_it(i, s, c, ssplit);
	if (i == -1)
		return (NULL);
	ssplit[i] = NULL;
	return (ssplit);
}

static int	ft_split_it(int i, char const *s, char c, char **ssplit)
{
	int	j;

	j = 0;
	while (i < ft_strs_count(s, c))
	{
		if (ft_len_beforesep(&s[j], c) > 0)
		{
			ssplit[i] = malloc(sizeof(char) * (ft_len_beforesep(&s[j], c) + 1));
			if (ssplit[i] == NULL)
			{
				j = -1;
				while (++j < i && ssplit[j])
					free(ssplit[j]);
				free(ssplit);
				return (-1);
			}
			ft_strcpy_untilsep(ssplit[i], &s[j], c);
			j += ft_len_beforesep(&s[j], c);
			i++;
		}
		else
			j++;
	}
	return (i);
}

static char	*ft_strcpy_untilsep(char *dest, char const *src, char sep)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != sep)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_len_beforesep(char const *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

static int	ft_strs_count(char const *str, char sep)
{
	int	s_count;
	int	i;

	s_count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i] == '\0')
			return (s_count);
		while (str[i] && str[i] != sep)
			i++;
		if (str[i] == '\0')
			s_count++;
		else
		{
			i++;
			s_count++;
		}
	}
	return (s_count);
}
