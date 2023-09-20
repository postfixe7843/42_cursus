/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlence-l <nlence-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:39:43 by jschmitt          #+#    #+#             */
/*   Updated: 2023/09/17 17:23:57 by nlence-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*new_value(char *str, char *var_value, int len, int new_len)
{
	int		i;
	int		j;
	char	*new_value;

	i = 0;
	j = 0;
	new_value = malloc(sizeof(char) * new_len);
	if (!new_value)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			cpy_str(new_value, var_value, &i, &j);
			j = i + len - ft_strlen(var_value) + 1;
			cpy_str(new_value, str, &i, &j);
			new_value[i] = 0;
			return (new_value);
		}
		else
			cpy_str(new_value, str, &i, NULL);
	}
	return (str);
}

char	*get_var_value(t_prompt *p, char *var_name)
{
	char	*var_value;

	var_value = NULL;
	if (ft_strlen(var_name) == 1 && ft_strcmp(var_name, "?") == 0)
		var_value = ft_itoa(p->last_pipeline_status);
	else
		var_value = mini_getenv(var_name, p->env);
	if (!var_value)
	{
		var_value = ft_strdup("");
		if (!var_value)
			return (NULL);
	}
	return (var_value);
}

static char	*exp_var(char *start_var, int len, t_prompt *p, char *str)
{
	char	*var_name;
	char	*var_value;
	char	*new_line;
	int		len_malloc;

	var_value = NULL;
	var_name = ft_substr(start_var, 1, len);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(p, var_name);
	free(var_name);
	if (!var_value)
		return (NULL);
	len_malloc = ft_strlen(str) - (len + 1) + ft_strlen(var_value) + 1;
	new_line = new_value(str, var_value, len, len_malloc);
	free(var_value);
	return (new_line);
}

char	*expand_heredoc(char *line, t_prompt *p)
{
	int	len;
	int	index;

	len = len_var(line);
	index = get_i_var(line);
	if (ft_strchr(line, '$'))
		return (exp_var(&line[index], len, p, line));
	return (line);
}

void	write_in_heredocsub1(char *exp_line, char *line,
	t_command *cmd, int *line_nbr)
{
	end_line(exp_line, cmd->in_fd);
	free(exp_line);
	line_nbr++;
	free(line);
}
