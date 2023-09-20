/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:03:19 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 16:54:53 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cpy_str(char *dest, char *src, int *i, int *j)
{
	if (!dest || !src)
		return ;
	if (j == NULL)
	{
		dest[*i] = src[*i];
		*i = *i + 1;
		return ;
	}
	while (src[*j])
	{
		dest[*i] = src[*j];
		*j = *j + 1;
		*i = *i + 1;
	}
}

void	replace_value(t_token *t, char *var_val, int len, int new_len)
{
	int		i;
	int		j;
	char	*new_value;

	i = 0;
	j = 0;
	new_value = malloc(sizeof(char) * (new_len + 1));
	while (new_value && t->value[i])
	{
		new_value[new_len] = 0;
		if (t->value[i] == '$' && (i == t->i_expand || t->type == TOKEN_KEEP_Q))
		{
			cpy_str(new_value, var_val, &i, &j);
			j = i + len - ft_strlen(var_val) + 1;
			cpy_str(new_value, t->value, &i, &j);
			new_value[i] = 0;
			free(t->value);
			t->value = new_value;
			return ;
		}
		else
			cpy_str(new_value, t->value, &i, NULL);
	}
	if (new_value)
		free(new_value);
}

int	replace_var_not_keep_qtok(char *val, char *name, int len, t_token *tok)
{
	int		len_malloc;

	len_malloc = ft_strlen(tok->value) - (len + 1) + ft_strlen(val) + 1;
	if (tok->type != TOKEN_KEEP_Q)
	{
		replace_value(tok, val, len, len_malloc);
		free(val);
		free(name);
		return (1);
	}
	return (0);
}

void	replace_var(char *start_var, int len, t_prompt *p, t_token *tok)
{
	char	*var_name;
	char	*var_value;

	var_value = NULL;
	var_name = ft_substr(start_var, 1, len);
	if (!var_name)
		return ;
	if (ft_strlen(var_name) == 1 && ft_strcmp(var_name, "?") == 0)
		var_value = ft_itoa(p->last_pipeline_status);
	else
		var_value = var_val_check(var_name, p, tok);
	if (!var_value)
	{
		var_value = ft_strdup("");
		if (!var_value)
		{
			free(var_name);
			return ;
		}
	}
	if (replace_var_not_keep_qtok(var_value, var_name, len, tok))
		return ;
	free(var_value);
	free(var_name);
}

void	expander(t_token **t, t_prompt *p)
{
	int	i;
	int	len;
	int	count;

	i = 0;
	while (t[i])
	{
		count = 0;
		t[i]->str_input = ft_strdup(t[i]->value);
		del_dollar(t[i]);
		while (get_i_var_toexpand(t[i]->value, p, count) != -1)
		{
			t[i]->i_expand = get_i_var_toexpand(t[i]->value, p, count);
			len = len_varname(t[i]->value, t[i]->i_expand);
			replace_var(get_var_toexpand(t[i], t[i]->value, p), len, p, t[i]);
			count++;
		}
		i++;
	}
	expander_sub1(t);
}
