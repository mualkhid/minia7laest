/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:55:32 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:18:37 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (!ft_memcmp(cmd_name, "echo", 5) || !ft_memcmp(cmd_name, "env", 4)
		|| !ft_memcmp(cmd_name, "export", 7) || !ft_memcmp(cmd_name, "unset", 6)
		|| !ft_memcmp(cmd_name, "cd", 3) || !ft_memcmp(cmd_name, "42", 3)
		|| !ft_memcmp(cmd_name, "pwd", 4) || !ft_memcmp(cmd_name, "exit", 5))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_cmd *cmd_parent, t_data *data)
{
	if (cmd->cmd_path == NULL)
		return (1);
	else if (!ft_memcmp(cmd->cmd_path, "echo", 5))
		g_exit_status = echo_cmd(cmd);
	else if (!ft_memcmp(cmd->cmd_path, "env", 4))
		g_exit_status = env_cmd(cmd, data);
	else if (!ft_memcmp(cmd->cmd_path, "export", 7))
		g_exit_status = export_cmd(cmd, data);
	else if (!ft_memcmp(cmd->cmd_path, "unset", 6))
		g_exit_status = unset_cmd(cmd, data);
	else if (!ft_memcmp(cmd->cmd_path, "cd", 3))
		g_exit_status = cd_cmd(cmd->cmd, data);
	else if (!ft_memcmp(cmd->cmd_path, "42", 3))
		g_exit_status = cmd_42(cmd);
	else if (!ft_memcmp(cmd->cmd_path, "pwd", 4))
		g_exit_status = pwd_cmd(cmd);
	else if (!ft_memcmp(cmd->cmd_path, "exit", 5))
		g_exit_status = exit_cmd(cmd, cmd_parent, data);
	else
		return (1);
	return (0);
}
