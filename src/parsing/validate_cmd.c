/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:53:20 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 13:50:23 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	chk_left_parenthesis(char *s, int i)
{
	if (i == 0)
		return (0);
	if (s[i - 1] == ' ' || s[i - 1] == '(')
		return (chk_left_parenthesis(s, i - 1));
	if (i > 1 && ((s[i - 1] == '&' && s[i - 2] == '&') || (s[i - 1] == '|'
				&& s[i - 2] == '|')))
		return (0);
	return (1);
}

static int	chk_right_parenthesis(char *s, size_t i)
{
	if (i == ft_strlen(s) - 1)
		return (0);
	if (s[i + 1] == ' ' || s[i + 1] == ')')
		return (chk_right_parenthesis(s, i + 1));
	if (i < ft_strlen(s) - 1 && ((s[i + 1] == '&' && s[i + 2] == '&') || (s[i
					+ 1] == '|' && s[i + 2] == '|')))
		return (0);
	return (1);
}

int	chk_parenthesis(char *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (quote == 0 && s[i] == '(' && chk_left_parenthesis(s, i))
			return (0);
		if (quote == 0 && s[i] == ')' && chk_right_parenthesis(s, i))
			return (0);
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (1);
}

int	chk_syntax(char *str)
{
	int	i;
	int	quote;
	int	paren_count;

	i = 0;
	paren_count = 0;
	quote = 0;
	while (str[i] && paren_count >= 0)
	{
		if (!quote && str[i] == '(')
			paren_count++;
		else if (!quote && str[i] == ')')
			paren_count--;
		else if (str[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (str[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	if (paren_count != 0 || quote > 0)
		return (0);
	return (1);
}
