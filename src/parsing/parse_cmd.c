/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:53:26 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 12:36:41 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	update_quote_state(const char c, int quote)
{
	if (c == '\'' && quote != 2)
		quote = (quote + 1) % 2;
	else if (c == '\"' && quote != 1)
		quote = (quote + 2) % 4;
	return (quote);
}

static char	*parse_parentheses(const char *s, size_t *i, int j)
{
	int		paren_count;
	char	*parsed_substring;
	int		last_char_i;
	int		quote;

	paren_count = 1;
	quote = 0;
	while (s[++j] && paren_count)
	{
		if (!quote && s[j] == '(')
			paren_count++;
		if (!quote && s[j] == ')')
			paren_count--;
		quote = update_quote_state(s[j], quote);
	}
	last_char_i = j;
	while (s[j] == ' ')
		j++;
	if (ft_memcmp(s + j, "&&", 2) && ft_memcmp(s + j, "||", 2) && s[j])
		return (0);
	parsed_substring = malloc(last_char_i - 1 - *i);
	ft_memcpy(parsed_substring, s + 1 + *i, last_char_i - 2 - *i);
	parsed_substring[last_char_i - 2 - *i] = 0;
	*i = j;
	return (parsed_substring);
}

static char	*parse_no_parentheses(char *s, size_t *i, int j)
{
	int	quote;
	int	operator_balance;
	int	paren_balance;

	operator_balance = 0;
	quote = 0;
	paren_balance = 0;
	while (s[j])
	{
		if (!quote && !paren_balance && (!ft_memcmp(s + j, "&&", 2)
				|| !ft_memcmp(s + j, "||", 2)))
		{
			*i = j;
			operator_balance++;
		}
		if (operator_balance == 2 || !s[j + 1])
			return (get_str(s, i, j));
		paren_balance += !quote * ((s[j] == '(') - (s[j] == ')'));
		quote = update_quote_state(s[j++], quote);
	}
	return (0);
}

static char	*get_next_segment(char *s, size_t *i)
{
	int	j;

	j = 0;
	while (s[j] == ' ')
		j++;
	*i = j;
	if (s[j] == '(')
		return (parse_parentheses(s, i, j));
	else
		return (parse_no_parentheses(s, i, j));
}

int	parse_cmd(t_cmd *cmd)
{
	size_t	i;
	char	*ncmd;
	char	*nncmd;

	i = 0;
	if (!cmd || !cmd->txt || is_logical_operator(cmd->txt))
		return (0);
	ncmd = get_next_segment(cmd->txt, &i);
	if (!ncmd)
		return (0);
	if (i + 2 <= ft_strlen(cmd->txt))
	{
		nncmd = ft_strdup(cmd->txt + i + 2);
		if (cmd->txt[i] == '&')
			cmd->on_success = add_to_cmd(nncmd);
		if (cmd->txt[i] == '|')
			cmd->on_fail = add_to_cmd(nncmd);
		free(nncmd);
	}
	cmd->next = add_to_cmd(ncmd);
	parse_cmd(cmd->next);
	parse_cmd(cmd->on_success);
	parse_cmd(cmd->on_fail);
	free(ncmd);
	return (1);
}
