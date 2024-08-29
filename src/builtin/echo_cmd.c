/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:55:45 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:41:04 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	new_line_flag(char **args, int *i)
{
	int	char_i;
	int	flag;

	*i = 1;
	flag = 1;
	while (flag && args[*i])
	{
		if (args[*i][0] == '-')
		{
			char_i = 1;
			while (args[*i][char_i] == 'n')
				char_i++;
			if (!args[*i][char_i] && char_i > 1)
				(*i)++;
			else
				flag = 0;
		}
		else
			flag = 0;
	}
	if (*i > 1)
		return (1);
	return (0);
}

static void	print_after_echo(char **args, int start_i, int fd_out)
{
	while (args[start_i])
	{
		ft_putstr_fd(args[start_i++], fd_out);
		if (args[start_i])
			ft_putstr_fd(" ", fd_out);
	}
}

static void	print_new_line(int n_flag, int fd_out)
{
	if (!n_flag)
		ft_putstr_fd("\n", fd_out);
}

int	echo_cmd(t_cmd *cmd)
{
	int	n_flag;
	int	arg_i;

	n_flag = new_line_flag(cmd->cmd, &arg_i);
	print_after_echo(cmd->cmd, arg_i, cmd->fd_out);
	print_new_line(n_flag, cmd->fd_out);
	return (0);
}
