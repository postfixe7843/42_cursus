/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:16:13 by jschmitt          #+#    #+#             */
/*   Updated: 2022/11/08 17:15:28 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*ss;

	i = -1;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	ss = malloc(sizeof(char) * (len + 1));
	if (ss == NULL)
		return (NULL);
	while (s[++i])
	{
		if (i >= start)
		{
			if (j < len)
				ss[j++] = s[i];
		}
	}
	ss[j] = '\0';
	return (ss);
}
