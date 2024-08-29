/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:54:05 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 02:00:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	parse_redir_op(char *s, t_list **words, size_t *i, int *d)
{
	if (!ft_memcmp(s + *i, ">>", 2))
	{
		ft_lstadd_back(words, ft_lstnew(ft_strdup(">>")));
		*d = *i + 2;
		(*i)++;
	}
	else if (!ft_memcmp(s + *i, ">", 1))
	{
		ft_lstadd_back(words, ft_lstnew(ft_strdup(">")));
		*d = *i + 1;
	}
	else if (!ft_memcmp(s + *i, "<<", 2))
	{
		ft_lstadd_back(words, ft_lstnew(ft_strdup("<<")));
		*d = *i + 2;
		(*i)++;
	}
	else if (!ft_memcmp(s + *i, "<", 1))
	{
		ft_lstadd_back(words, ft_lstnew(ft_strdup("<")));
		*d = *i + 1;
	}
	else
		return (0);
	return (1);
}

static int	add_word(char *s, t_list **words, size_t *i, int *d)
{
	char	*string;

	string = ft_substr(s, *d, *i - *d);
	if (!string)
		return (0);
	if (only_space(string))
	{
		free(string);
		if (*words != 0)
			return (0);
	}
	else
	{
		ft_lstadd_back(words, ft_lstnew(string));
		if (!ft_lstlast(*words)->content)
			return (0);
	}
	if (parse_redir_op(s, words, i, d) && !ft_lstlast(*words)->content)
		return (0);
	return (1);
}

static int	is_redir_operator(char *s)
{
	if (!ft_memcmp(s, ">>", 2) || !ft_memcmp(s, ">", 1))
		return (1);
	else if (!ft_memcmp(s, "<<", 2) || !ft_memcmp(s, "<", 1))
		return (1);
	else
		return (0);
}

static char	**list_to_string_array(t_list *words)
{
	char	**word_array;

	word_array = convert_to_aos(words);
	ft_lstclear(&words, &free);
	return (word_array);
}

char	**parse_redir_cmd(char *s)
{
	t_list	*words;
	size_t	i;
	int		d;
	int		quote;

	d = 0;
	quote = 0;
	words = 0;
	i = -1;
	while (++i <= ft_strlen(s))
	{
		if ((!s[i] || is_redir_operator(s + i)) && quote == 0)
		{
			if (!add_word(s, &words, &i, &d))
			{
				ft_lstclear(&words, &free);
				return (NULL);
			}
		}
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
	}
	return (list_to_string_array(words));
}
