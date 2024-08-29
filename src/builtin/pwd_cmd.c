/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:56:15 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 06:35:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd_cmd(t_cmd *cmd)
{
	char	*pwd;

	pwd = get_pwd();
	if (pwd == NULL)
		return (1);
	ft_putendl_fd(pwd, cmd->fd_out);
	free(pwd);
	return (0);
}

char	*get_pwd(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * 4096);
	if (pwd == NULL)
		return (NULL);
	if (getcwd(pwd, 4096) == NULL)
	{
		perror("getcwd");
		free(pwd);
		return (NULL);
	}
	return (pwd);
}
