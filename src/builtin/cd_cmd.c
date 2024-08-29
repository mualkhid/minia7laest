/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:55:37 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 12:56:11 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_pwd(t_data *data)
{
	t_list	*lst;
	char	*pwd;
	char	*new_content;

	lst = data->env;
	while (lst)
	{
		if (!ft_memcmp("PWD=", (char *)lst->content, 4))
		{
			pwd = get_pwd();
			if (pwd == NULL)
				return ;
			new_content = ft_strjoin("PWD=", pwd);
			free(pwd);
			if (new_content == NULL)
				return ;
			free(lst->content);
			lst->content = new_content;
			return ;
		}
		lst = lst->next;
	}
}

static char	*get_abs_path(char *path, t_data *data)
{
	char	*home;
	char	*pwd;
	char	*temp;

	if (path == NULL)
	{
		home = get_env_var_value("HOME", data);
		if (home == NULL)
			ft_putendl_fd("cd: HOME not set", 2);
		return (ft_strdup(home));
	}
	else if (!is_it_in_str(path, '/'))
	{
		path = ft_strjoin("/", path);
		if (path == NULL)
			return (NULL);
		pwd = get_pwd();
		temp = ft_strjoin(pwd, path);
		free(path);
		free(pwd);
		return (temp);
	}
	return (ft_strdup(path));
}

static int	handle_cd_error(char *absolute_path, char *path)
{
	if (access(absolute_path, F_OK))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	else if (ft_if_file(absolute_path))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (1);
	}
	else if (access(absolute_path, X_OK))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

int	cd_cmd(char **cmd, t_data *data)
{
	char	*absolute_path;

	if (cmd == NULL || (cmd[1] != NULL && cmd[2] != NULL))
	{
		ft_putendl_fd("cd : too many arguments", 2);
		return (1);
	}
	absolute_path = get_abs_path(cmd[1], data);
	if (absolute_path == NULL || handle_cd_error(absolute_path, cmd[1]))
	{
		free(absolute_path);
		return (1);
	}
	if (chdir(absolute_path))
	{
		perror("chdir");
		free(absolute_path);
		return (1);
	}
	free(absolute_path);
	update_pwd(data);
	return (0);
}
