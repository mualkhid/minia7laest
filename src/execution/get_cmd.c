/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:55:09 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:22:03 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	coloring(char **line)
{
	char	*temp;

	temp = *line;
	if (g_exit_status)
		*line = ft_strjoin("\e[1;31m➜ \e[1;36m minishell: \e[1;34m", temp);
	else
		*line = ft_strjoin("\e[1;32m➜ \e[1;36m minishell: \e[1;34m", temp);
	free(temp);
	temp = *line;
	*line = ft_strjoin(temp, " $> \e[0m");
	free(temp);
}

static int	get_startingline(char **line, t_data *data)
{
	char	*pwd;
	char	*home;

	pwd = get_pwd();
	if (pwd == NULL)
		return (0);
	home = get_env_var_value("HOME", data);
	if (home && !ft_memcmp(pwd, home, ft_strlen(home)))
	{
		*line = ft_strjoin("~", pwd + ft_strlen(home));
		free(pwd);
	}
	else
		*line = pwd;
	coloring(line);
	if (*line == NULL)
		return (0);
	return (1);
}

t_cmd	*get_cmd(t_data *data)
{
	char	*startingline;
	char	*initial;
	t_cmd	*cmd;

	cmd = 0;
	if (!get_startingline(&startingline, data))
		return (0);
	initial = readline(startingline);
	free(startingline);
	if (!initial)
		return (0);
	if (!only_space(initial))
		add_history(initial);
	parse_group(&cmd, initial, data);
	free(initial);
	return (cmd);
}
