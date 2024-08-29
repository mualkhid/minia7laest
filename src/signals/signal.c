/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:52:46 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:28:26 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ctrl_c_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	get_sig_during_cmd(void)
{
	if (signal(SIGINT, ctrl_c_handler) == SIG_ERR)
		printf("A signal error happened\n");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		printf("A signal error happened\n");
}

void	exec_signal(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		printf("A signal error happened\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		printf("A signal error happened\n");
}

void	nothing_signal(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		printf("A signal error happened\n");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		printf("A signal error happened\n");
}

void	sig_during_cmd(int sig)
{
	if (sig == 2)
	{
		ft_putstr_fd("\n", 1);
		g_exit_status = 130;
	}
	else if (sig == 3)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_exit_status = 131;
	}
}
