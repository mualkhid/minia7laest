/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:55:16 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:25:24 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	read_stdin(char *limiter, int fd)
{
	char	*line;
	int		len;

	len = ft_strlen(limiter);
	line = readline("> ");
	while (line && ft_memcmp(line, limiter, len + 1))
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	else
	{
		ft_putstr_fd("Warning : here-document delemited ", 1);
		ft_putstr_fd("by end-of-file ( wanted `", 1);
		ft_putstr_fd(limiter, 1);
		ft_putstr_fd("\' )\n", 1);
	}
}

static int	create_child(int pipefds[2], char *limiter, t_cmd *cmd_parent,
		t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close_fd(pipefds[0]);
		free_aos(cmd_parent->initials);
		ft_lstclear(&(data->env), &free);
		free_cmd(cmd_parent);
		before_sig_info(1, pipefds[1], limiter);
		if (signal(SIGINT, ctrl_c_heredoc) == SIG_ERR)
			printf("heu le signal deconne/n");
		read_stdin(limiter, pipefds[1]);
		before_sig_info(0, 0, NULL);
		rl_clear_history();
		close(0);
		close(1);
		close(2);
		exit(0);
	}
	return (pid);
}

static int	check_signal_child(int pipefds[2], int status, t_cmd *cmd)
{
	if (!(status & 0x7f))
	{
		g_exit_status = (status >> 8) & 0xFF;
		if (g_exit_status == 130)
		{
			close_fd(pipefds[0]);
			ft_putstr_fd("\n", 1);
			g_exit_status = 130;
			return (0);
		}
	}
	else
	{
		close_fd(pipefds[0]);
		ft_putstr_fd("\n", 1);
		g_exit_status = 130;
		return (0);
	}
	cmd->fd_heredocs = pipefds[0];
	return (1);
}

int	redir_in_heredoc(char *limiter_initial, t_cmd *cmd, t_cmd *cmd_parent,
		t_data *data)
{
	int		pid;
	int		pipefds[2];
	int		status;
	char	*limiter;

	close_fd(cmd->fd_heredocs);
	cmd->fd_heredocs = -1;
	limiter = strdup_unquoted(limiter_initial);
	if (!limiter)
		return (0);
	if (pipe(pipefds) == -1)
		perror("pipe");
	else
	{
		pid = create_child(pipefds, limiter, cmd_parent, data);
		nothing_signal();
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid");
		get_sig_during_cmd();
		close_fd(pipefds[1]);
		free(limiter);
		return (check_signal_child(pipefds, status, cmd));
	}
	free(limiter);
	return (0);
}

int	redir_in_stdin(char *filename_initial, t_cmd *cmd, t_data *data)
{
	char	*filename;

	if (cmd->fd_in != cmd->fd_heredocs)
		close_fd(cmd->fd_in);
	filename = find_filename(filename_initial, data);
	if (filename)
	{
		cmd->fd_in = open(filename, O_RDONLY);
		if (cmd->fd_in == -1)
			perror("open");
	}
	else
	{
		free(filename);
		g_exit_status = 1;
		ft_putstr_fd("wrong redirect\n", 2);
		cmd->fd_in = -1;
		return (0);
	}
	free(filename);
	return (1);
}
