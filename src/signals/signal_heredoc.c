/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:52:52 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/20 18:52:54 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	before_sig_info(int mode, int fd, char *limiter)
{
	static int	fd_save;
	static char	*limiter_save;

	if (mode == 1)
	{
		fd_save = fd;
		limiter_save = limiter;
	}
	else
	{
		close_fd(fd_save);
		free(limiter_save);
		fd_save = -1;
		limiter_save = NULL;
	}
}

void	ctrl_c_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		before_sig_info(0, 0, NULL);
		rl_clear_history();
		close(0);
		close(1);
		close(2);
		exit(130);
	}
}
