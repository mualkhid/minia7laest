/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:53:57 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 02:00:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	add_word(char *string, char *c, t_list **words)
{
	if (!string)
		return (0);
	if (ft_strlen(string))
	{
		ft_lstadd_back(words, ft_lstnew(string));
		if (!ft_lstlast(*words)->content)
			return (0);
	}
	else
	{
		free(string);
		if (!ft_memcmp(c, "|", 2))
			return (0);
	}
	return (1);
}

static char	**free_lst_return_tab(t_list **words, char **strings_array)
{
	ft_lstclear(words, &free);
	return (strings_array);
}

char	**split_string(char *s, char *c)
{
	t_list	*words;
	char	**strings_array;
	size_t	i;
	int		start_i;
	int		quote;

	start_i = 0;
	quote = 0;
	words = 0;
	i = -1;
	while (++i <= ft_strlen(s))
	{
		if ((!ft_memcmp(s + i, c, ft_strlen(c)) || !s[i]) && quote == 0)
		{
			if (!add_word(ft_substr(s, start_i, i - start_i), c, &words))
				return (free_lst_return_tab(&words, NULL));
			start_i = i + ft_strlen(c);
		}
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
	}
	strings_array = convert_to_aos(words);
	return (free_lst_return_tab(&words, strings_array));
}
