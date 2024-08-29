/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:53:45 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:23:35 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_substring(char *s, char *c)
{
	int		i;
	char	*new_str;

	i = 1;
	while (s[i] && !check_if_in(s[i], c))
		i++;
	if (i == 1 && (s[i] == '\0' || s[i] == ' '))
		return (NULL);
	new_str = malloc(i + 1);
	if (!new_str)
		return (0);
	i = 0;
	while (s[i] && (i == 0 || !check_if_in(s[i], c)))
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

static int	set_var_value(char **var_name, char **var_value, int *pos,
		t_data *data)
{
	if (!*var_name)
	{
		(*pos)++;
		free(*var_name);
		return (1);
	}
	if (ft_memcmp(*var_name, "$?", 2))
		*var_value = ft_strdup(get_env_var_value(*var_name + 1, data));
	else
		*var_value = ft_itoa(g_exit_status);
	return (0);
}

void	replace_var(char **s, int *pos, t_data *data)
{
	char	*new_str;
	char	*var_name;
	char	*var_value;

	var_name = get_substring((*s) + *pos, "' $\"");
	if (set_var_value(&var_name, &var_value, pos, data))
		return ;
	new_str = malloc(ft_strlen(*s) - ft_strlen(var_name) + ft_strlen(var_value)
			+ 1);
	if (!new_str)
	{
		free(var_name);
		free(var_value);
		return ;
	}
	ft_memcpy(new_str, *s, *pos);
	ft_memcpy(new_str + *pos, var_value, ft_strlen(var_value));
	ft_memcpy(new_str + *pos + ft_strlen(var_value), (*s) + *pos
		+ ft_strlen(var_name), ft_strlen((*s) + *pos + ft_strlen(var_name))
		+ 1);
	free(*s);
	*pos = *pos + ft_strlen(var_value);
	*s = new_str;
	free(var_value);
	free(var_name);
}

int	parse_double_quotes(char **s, int *i, t_data *data)
{
	char	*new_str;
	int		pos;

	pos = *i + 1;
	while ((*s)[pos] && (*s)[pos] != '"')
	{
		if ((*s)[pos] == '$')
			replace_var(s, &pos, data);
		else
			pos++;
	}
	if (!(*s)[pos])
	{
		free(*s);
		return (1);
	}
	new_str = malloc(ft_strlen(*s) - 1);
	new_str[ft_strlen(*s) - 2] = 0;
	ft_memcpy(new_str, *s, *i);
	ft_memcpy(new_str + *i, *s + *i + 1, pos - *i - 1);
	ft_memcpy(new_str + pos - 1, *s + pos + 1, ft_strlen(*s + pos + 1));
	*i = pos - 1;
	free(*s);
	*s = new_str;
	return (0);
}

int	parse_single_quotes(char **s, int *i)
{
	char	*new_str;
	int		pos;

	pos = *i + 1;
	while ((*s)[pos] && (*s)[pos] != '\'')
		pos++;
	if (!(*s)[pos])
	{
		free(*s);
		return (1);
	}
	new_str = malloc(ft_strlen(*s) - 1);
	new_str[ft_strlen(*s) - 2] = 0;
	ft_memcpy(new_str, *s, *i);
	ft_memcpy(new_str + *i, *s + *i + 1, pos - *i - 1);
	ft_memcpy(new_str + pos - 1, *s + pos + 1, ft_strlen(*s + pos + 1));
	*i = pos - 1;
	free(*s);
	*s = new_str;
	return (0);
}
