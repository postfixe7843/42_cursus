/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmitt <jschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:52:11 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/18 14:34:08 by jschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_between_nested_dquotes(char *str, int i)
{
	int	count_before;
	int	count_after;

	count_before = 0;
	count_after = count_quotes_after(str, i);
	while (i >= 0)
	{
		if (str[i] == '"')
			count_before++;
		i--;
	}
	if (count_before % 2)
		return (1);
	else if (count_before == count_after && count_before % 2)
		return (1);
	else if (count_before >= 2 && count_before % 2 == 0)
		return (2);
	return (0);
}

static char	*value_clean_space(char *str, int add_space_at_start, char *input)
{
	char	**split;
	char	*joined;
	int		i;

	i = 0;
	split = NULL;
	if (str)
		split = ft_split(str, ' ');
	if (add_space_at_start && str[0] == ' ')
		joined = ft_strdup(" ");
	else
		joined = ft_strdup("");
	while (split[i])
	{
		joined = join_msg(joined, split[i]);
		free(split[i]);
		if (split[i + 1] || ((!ft_isalnum(input[ft_strlen(input) - 1])
					|| input[ft_strlen(input) - 1] == '"')
				&& str[ft_strlen(str) - 1] == ' '))
			joined = join_msg(joined, " ");
		i++;
	}
	free(split);
	free(str);
	return (joined);
}

char	*var_value_checked(char *val, t_prompt *p, t_token *t)
{
	char	*var_value;
	int		i;

	if (!val)
		return (NULL);
	i = get_i_var_toexpand(t->value, p, 0);
	if (is_between_nested_dquotes(t->value, i) == 2)
		var_value = value_clean_space(val, 1, t->str_input);
	else if (is_between_nested_dquotes(t->value, i) == 0)
		var_value = value_clean_space(val, 0, t->str_input);
	else
		var_value = val;
	return (var_value);
}

void	update_token_type(char *val, t_token *t, int i)
{
	if (!val)
		return ;
	if ((val[0] == ' ' && is_between_nested_dquotes(t->value, i) != 0
			&& t->type != TOKEN_KEEP_Q)
		|| (t->type != TOKEN_KEEP_Q && val[ft_strlen(val) - 1] == ' '))
		t->type = TOKEN_WORD;
}

char	*var_val_check(char *v_name, t_prompt *p, t_token *t)
{
	char	*var_value;
	char	*tmp;
	int		i;
	int		len;
	int		new_len;

	i = get_i_var_toexpand(t->value, p, 0);
	tmp = mini_getenv(v_name, p->env);
	if (!tmp)
		return (NULL);
	if ((ft_strchr(tmp, '\'') || ft_strchr(tmp, '"')))
	{
		var_value = var_value_checked(tmp, p, t);
		if (!var_value)
			return (NULL);
		len = len_varname(t->value, t->i_expand);
		new_len = ft_strlen(t->value) - (len + 1) + ft_strlen(var_value) + 1;
		handle_quotes(t);
		t->type = TOKEN_KEEP_Q;
		replace_value(t, var_value, len, new_len);
	}
	else
		var_value = var_value_checked(tmp, p, t);
	update_token_type(var_value, t, i);
	return (var_value);
}
