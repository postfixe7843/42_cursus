/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:48:57 by jschmitt          #+#    #+#             */
/*   Updated: 2022/11/08 17:20:56 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_isinset(s1[start], set))
		start++;
	while (end > start && ft_isinset(s1[end - 1], set))
		end--;
	strim = malloc(sizeof(char) * (end - start + 1));
	if (strim == NULL)
		return (NULL);
	while (start < end)
	{
		strim[i] = s1[start];
		i++;
		start++;
	}
	strim[i] = '\0';
	return (strim);
}

static int	ft_isinset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
