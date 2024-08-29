/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:54:50 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/20 18:54:51 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	split_words(t_cmd *cmd, int i, t_data *data)
{
	char	**split;

	split = cmd->parsing_pre_analysis;
	if (!ft_memcmp(split[i], ">>", 3))
		return (redir_in_append(split[i + 1], &(cmd->fd_out), data));
	else if (!ft_memcmp(split[i], ">", 2))
		return (redir_in_stdout(split[i + 1], &(cmd->fd_out), data));
	else if (!ft_memcmp(split[i], "<<", 3))
	{
		if (cmd->fd_in != cmd->fd_heredocs)
			close_fd(cmd->fd_in);
		cmd->fd_in = cmd->fd_heredocs;
		return (1);
	}
	else if (!ft_memcmp(split[i], "<", 2))
		return (redir_in_stdin(split[i + 1], cmd, data));
	return (2);
}

static void	add_word_tranform(char *word, t_list **words, t_data *data)
{
	char	**wildcards;
	char	*string;
	int		j;

	if (check_if_in_special('*', word))
	{
		wildcards = do_wildcards_word(word, data);
		if (!wildcards || !wildcards[0])
			ft_lstadd_back(words, ft_lstnew(exec_transformation(ft_strdup(word),
						data)));
		else
		{
			j = -1;
			while (wildcards[++j])
				ft_lstadd_back(words, ft_lstnew(ft_strdup(wildcards[j])));
		}
		free_aos(wildcards);
	}
	else
	{
		string = exec_transformation(ft_strdup(word), data);
		if (string)
			ft_lstadd_back(words, ft_lstnew(string));
	}
}

static char	**create_cmd_aos(t_list *words, t_cmd *cmd)
{
	char	**tab;

	tab = convert_to_aos(words);
	ft_lstclear(&words, &free);
	if (cmd->fd_in == cmd->fd_heredocs)
		cmd->fd_heredocs = -1;
	return (tab);
}

char	**do_redirections(t_cmd *cmd, t_data *data)
{
	t_list	*words;
	int		value;
	int		i;
	char	**split;

	split = cmd->parsing_pre_analysis;
	words = 0;
	if (!split)
		return (NULL);
	i = -1;
	while (split[++i])
	{
		value = split_words(cmd, i, data);
		if (value == 0)
		{
			ft_lstclear(&words, &free);
			return (NULL);
		}
		else if (value == 1)
			i++;
		else
			add_word_tranform(split[i], &words, data);
	}
	return (create_cmd_aos(words, cmd));
}

int	check_if_in_special(char c, char *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (c == s[i] && !quote)
			return (1);
		if (s[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (s[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (0);
}
