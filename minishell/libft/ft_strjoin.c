/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:32:19 by jschmitt          #+#    #+#             */
/*   Updated: 2022/11/08 17:18:43 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s1_len;
	int		len_joined;
	char	*str_joined;

	i = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	len_joined = s1_len + ft_strlen(s2);
	str_joined = malloc(sizeof(char) * (len_joined + 1));
	if (str_joined == NULL)
		return (NULL);
	while (s1[++i])
		str_joined[i] = s1[i];
	i = -1;
	while (s2[++i])
		str_joined[i + s1_len] = s2[i];
	str_joined[len_joined] = '\0';
	return (str_joined);
}
