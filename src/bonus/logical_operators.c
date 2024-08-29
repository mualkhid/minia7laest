/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:54:14 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:17:55 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_logical_operator(char *txt)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (txt[i] == ' ')
		i++;
	if (txt[i] == '(')
		return (0);
	while (txt[i])
	{
		if (!quote && txt[i] == '&' && txt[i + 1] == '&')
			return (0);
		if (!quote && txt[i] == '|' && txt[i + 1] == '|')
			return (0);
		if (txt[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if (txt[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (1);
}

static int	prepare_line_for_parsing(t_cmd **cmd, t_cmd **cmd_parent,
		t_data *data)
{
	int	ret;

	if (!cmd || !*cmd)
		return (1);
	if ((*cmd)->next)
		ret = prepare_line_for_parsing(&(*cmd)->next, cmd_parent, data);
	else
		ret = preprocess_cmd(cmd, (*cmd)->txt, *cmd_parent, data);
	if (ret != 1)
		return (ret);
	ret = prepare_line_for_parsing(&(*cmd)->on_fail, cmd_parent, data);
	if (ret != 1)
		return (ret);
	ret = prepare_line_for_parsing(&(*cmd)->on_success, cmd_parent, data);
	if (ret != 1)
		return (ret);
	return (1);
}

static void	handle_command_error(t_cmd **cmd)
{
	if (*cmd)
		free_cmd(*cmd);
	ft_putstr_fd("syntax error\n", 2);
	g_exit_status = 2;
	*cmd = init_cmd_struct();
}

void	parse_group(t_cmd **cmd, char *initial, t_data *data)
{
	int	ret;

	if (!initial)
		return ;
	if (only_space(initial))
		*cmd = init_cmd_struct();
	else if (!chk_syntax(initial) || !chk_parenthesis(initial))
		handle_command_error(cmd);
	else
	{
		*cmd = add_to_cmd(initial);
		parse_cmd(*cmd);
		ret = prepare_line_for_parsing(cmd, cmd, data);
		if (ret == 0)
			handle_command_error(cmd);
		else if (ret == -1)
		{
			free_cmd(*cmd);
			*cmd = init_cmd_struct();
		}
	}
}
