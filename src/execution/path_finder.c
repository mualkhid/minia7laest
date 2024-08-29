/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:55:04 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 18:21:34 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**find_path(t_list *env)
{
	char	*var_path;

	var_path = NULL;
	while (!var_path && env != NULL)
	{
		if (!ft_memcmp("PATH=", env->content, 5))
			var_path = env->content;
		env = env->next;
	}
	if (var_path == NULL)
		return (NULL);
	return (ft_split(var_path + 5, ':'));
}

static char	*find_cmd_path_with_name(char *cmd_name)
{
	if (access(cmd_name, F_OK) || ft_if_file(cmd_name))
	{
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putchar_fd('\n', 2);
		return (NULL);
	}
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	g_exit_status = 126;
	return (NULL);
}

static char	*find_cmd_absolute_path(char *cmd_name, t_list *env)
{
	char	**path;
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	if (cmd_name && cmd_name[0] != '\0')
	{
		path = find_path(env);
		if (path == NULL)
			return (NULL);
		cmd_name = ft_strjoin("/", cmd_name);
		i = -1;
		while (cmd_name && !cmd_path && path[++i])
		{
			cmd_path = ft_strjoin(path[i], cmd_name);
			if (cmd_path && access(cmd_path, X_OK))
			{
				free(cmd_path);
				cmd_path = NULL;
			}
		}
		free(cmd_name);
		free_aos(path);
	}
	return (cmd_path);
}

static char	*find_cmd_name(char **cmd)
{
	if (!cmd)
		return (NULL);
	return (cmd[0]);
}

char	*find_cmd_path(char **cmd, t_list *env)
{
	char	*cmd_name;
	char	*cmd_path;

	cmd_name = find_cmd_name(cmd);
	if (cmd_name == NULL)
		return (NULL);
	if (is_in_builtin(cmd_name))
		cmd_path = ft_strdup(cmd_name);
	else if (is_it_in_str(cmd_name, '/'))
		cmd_path = find_cmd_path_with_name(cmd_name);
	else
	{
		cmd_path = find_cmd_absolute_path(cmd_name, env);
		if (cmd_path == NULL)
		{
			ft_putstr_fd("Command not found: ", 2);
			ft_putstr_fd(cmd_name, 2);
			ft_putchar_fd('\n', 2);
			g_exit_status = 127;
		}
	}
	return (cmd_path);
}
