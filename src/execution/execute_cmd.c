/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:54:55 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:39:01 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	analyse_line(t_cmd *cmd, t_data *data)
{
	if (!cmd)
		return ;
	cmd->cmd = do_redirections(cmd, data);
	analyse_line(cmd->pipe, data);
}

int	check_cmds(t_cmd *cmd, t_cmd *cmd_parent, t_data *data)
{
	if (cmd->next)
	{
		if (!check_cmds(cmd->next, cmd_parent, data))
			return (0);
	}
	else
	{
		if (!exec_cmd(cmd, cmd_parent, data))
			return (0);
	}
	if (cmd->on_fail && g_exit_status)
	{
		if (!check_cmds(cmd->on_fail, cmd_parent, data))
			return (0);
	}
	if (cmd->on_success && !g_exit_status)
	{
		if (!check_cmds(cmd->on_success, cmd_parent, data))
			return (0);
	}
	return (1);
}

static int	handle_signal(int g_exit_status)
{
	int	signal_number;

	signal_number = g_exit_status & 0x7F;
	if (signal_number != 0)
	{
		sig_during_cmd(signal_number);
		return (0);
	}
	return (1);
}

static int	process_command(t_cmd *cmd, int *g_exit_status)
{
	if (cmd->pid != -1 && waitpid(cmd->pid, g_exit_status, 0) == -1)
	{
		perror("waitpid");
		return (0);
	}
	return (handle_signal(*g_exit_status));
}

int	wait_cmd(t_cmd *cmd, t_cmd *cmd_parent)
{
	(void)cmd_parent;
	while (cmd)
	{
		if (!process_command(cmd, &g_exit_status))
			return (0);
		cmd = cmd->pipe;
	}
	if ((g_exit_status & 0x7F) == 0)
		g_exit_status = (g_exit_status >> 8) & 0xFF;
	else
		return (handle_signal(g_exit_status));
	return (1);
}
