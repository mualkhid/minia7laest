/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:52:06 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/20 18:52:08 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_header(int fd)
{
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("\e[1;34m", fd);
	ft_putstr_fd("#####################################################\n", fd);
	ft_putstr_fd("\e[1;34m   ___  _____   __  __\e[0;36m      "
		"         _          _ _\n", fd);
	ft_putstr_fd("\e[1;34m  /   |/ __  \\ |  \\/  \e[0;36m(_) "
		"    (_)   | |        | | |\n", fd);
	ft_putstr_fd("\e[1;34m / /| |`' / /' | .  . |\e[0;36m_ _ _"
		"_  _ ___| |__   ___| | |\n", fd);
	ft_putstr_fd("\e[1;34m/ /_| |  / /   | |\\/| |\e[0;36m | '"
		"_ \\| / __| '_ \\ / _ \\ | |\n", fd);
	ft_putstr_fd("\e[1;34m\\___  |./ /___ | |  | |\e[0;36m | |"
		" | | \\__ \\ | | |  __/ | |\n", fd);
	ft_putstr_fd("\e[1;34m    |_/\\_____/ \\_|  |_/\e[0;36m_|_"
		"| |_|_|___/_| |_|\\___|_|_|\n", fd);
	ft_putstr_fd("\e[1;34m\n", fd);
	ft_putstr_fd("#####################################################\n", fd);
	ft_putstr_fd("\e[0m", fd);
	ft_putstr_fd("\e[0;36m By\e[1;34m mualkhid\e[0;36m &\e[1;34m maiahmed\n",
		fd);
	ft_putstr_fd("\e[0m", fd);
	ft_putstr_fd("\n", fd);
}

int	cmd_42(t_cmd *cmd)
{
	print_header(cmd->fd_out);
	return (0);
}
