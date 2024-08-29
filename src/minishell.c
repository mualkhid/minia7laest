/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:51:56 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:36:52 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_cmd	*cmd;

	(void)av;
	(void)ac;
	data.env = parse_env_vars(envp);
	set_pwd(&data);
	print_header(0);
	shlvl(&data);
	while (42)
	{
		get_sig_during_cmd();
		cmd = get_cmd(&data);
		if (cmd)
			check_cmds(cmd, cmd, &data);
		else
			exit_cmd(cmd, cmd, &data);
		free_cmd(cmd);
	}
	cleanup_exit(&data, NULL);
	return (0);
}
