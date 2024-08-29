/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:53:33 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/28 23:09:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	len_unquoted_chars(char *input_str)
{
	int	len;
	int	quote;
	int	i;

	i = -1;
	len = 0;
	quote = 0;
	while (input_str[++i])
	{
		if (input_str[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (input_str[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		else
			len++;
	}
	return (len);
}

char	*strdup_unquoted(char *input_str)
{
	char	*dup_str;
	int		i;
	int		j;
	int		quote;

	if (!input_str)
		return (NULL);
	dup_str = malloc(sizeof(char) * (len_unquoted_chars(input_str) + 1));
	if (!dup_str)
		return (NULL);
	i = -1;
	j = -1;
	quote = 0;
	while (input_str[++i])
	{
		if (input_str[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (input_str[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		else
			dup_str[++j] = input_str[i];
	}
	dup_str[++j] = '\0';
	return (dup_str);
}
