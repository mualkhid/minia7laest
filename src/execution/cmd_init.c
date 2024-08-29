/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:54:45 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/20 18:54:46 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*init_cmd_struct(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->pipe = 0;
	cmd->on_success = 0;
	cmd->on_fail = 0;
	cmd->next = 0;
	cmd->cmd = 0;
	cmd->txt = 0;
	cmd->cmd_path = 0;
	cmd->parsing_pre_analysis = 0;
	cmd->pipe = 0;
	cmd->fd_heredocs = -1;
	cmd->bonus = 0;
	return (cmd);
}

t_cmd	*add_to_cmd(char *txt)
{
	t_cmd	*cmd;

	cmd = init_cmd_struct();
	if (!cmd)
		return (0);
	cmd->txt = ft_strdup(txt);
	cmd->bonus = !(is_logical_operator(txt));
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->pipe)
		free_cmd(cmd->pipe);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd)
		free_aos(cmd->cmd);
	if (cmd->txt)
		free(cmd->txt);
	if (cmd->next)
		free_cmd(cmd->next);
	if (cmd->parsing_pre_analysis)
		free_aos(cmd->parsing_pre_analysis);
	close_fd(cmd->fd_heredocs);
	if (cmd->on_fail)
		free_cmd(cmd->on_fail);
	if (cmd->on_success)
		free_cmd(cmd->on_success);
	free(cmd);
}
