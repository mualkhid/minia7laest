/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:53:50 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 13:44:54 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_here_docs(t_cmd *cmd, t_cmd *cmd_parent, t_data *data)
{
	int		i;
	char	**split;

	split = cmd->parsing_pre_analysis;
	if (!split)
		return (1);
	i = -1;
	while (split[++i])
	{
		if (!ft_memcmp(split[i], "<<", 3))
		{
			if (!redir_in_heredoc(split[i + 1], cmd, cmd_parent, data))
				return (0);
			i++;
		}
	}
	return (1);
}

static char	**split_redir_and_space(char *cmd_str)
{
	char	**split;
	char	*new_str;

	split = parse_redir_cmd(cmd_str);
	if (!split)
		return (NULL);
	new_str = join_strings(aos_len(split), split, " ");
	free_aos(split);
	if (!new_str)
		return (0);
	split = split_string(new_str, " ");
	free(new_str);
	return (split);
}

static int	preprocess_line_without_pipe(t_cmd **cmd, char **cmd_str,
		t_cmd *cmd_parent, t_data *data)
{
	char	**split;

	if (!cmd_str)
		return (0);
	if (!*cmd_str)
		return (1);
	if (only_space(*cmd_str))
		return (0);
	if (!*cmd)
		*cmd = init_cmd_struct();
	split = split_redir_and_space(*cmd_str);
	if (!split)
		return (0);
	(*cmd)->parsing_pre_analysis = split;
	if (!handle_here_docs(*cmd, cmd_parent, data))
		return (-1);
	return (preprocess_line_without_pipe(&((*cmd)->pipe), cmd_str + 1,
			cmd_parent, data));
}

int	preprocess_cmd(t_cmd **cmd, char *str, t_cmd *cmd_parent, t_data *data)
{
	char	**cmd_str;
	int		ret;

	cmd_str = split_string(str, "|");
	cmd_parent->initials = cmd_str;
	ret = preprocess_line_without_pipe(cmd, cmd_str, cmd_parent, data);
	free_aos(cmd_str);
	cmd_parent->initials = NULL;
	if (ret != 1)
		return (ret);
	return (1);
}
