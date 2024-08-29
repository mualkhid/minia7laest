/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:56:04 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 02:12:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_var_name_export(char *name, int j)
{
	if (j == 0)
	{
		if (ft_isalpha(name[j]) || name[j] == '_')
			return (1);
		return (0);
	}
	if (ft_isalpha(name[j]) || ft_isdigit(name[j]) || name[j] == '_')
		return (1);
	return (0);
}

static char	*strdup_no_plus(const char *s)
{
	int		i;
	int		plus;
	char	*dup_str;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	dup_str = (char *)malloc(sizeof(char) * i);
	if (!dup_str)
		return (0);
	plus = 0;
	i = 0;
	while (s[i])
	{
		if (!plus && s[i] == '+')
			plus = 1;
		else
			dup_str[i - plus] = s[i];
		i++;
	}
	dup_str[i - plus] = s[i];
	return (dup_str);
}

static void	update_or_add_env_var(t_data *data, char *var, int j, int added)
{
	t_list	*lst;
	char	*new_content;

	lst = data->env;
	while (lst && !added)
	{
		if (!ft_strncmp(var, (char *)lst->content, j))
			added = 1;
		else
			lst = lst->next;
	}
	if (var[j] == '=')
		new_content = ft_strdup(var);
	else if (added)
		new_content = join_var_with_content(lst->content, var + j + 2);
	else
		new_content = strdup_no_plus(var);
	if (added && new_content)
	{
		free(lst->content);
		lst->content = new_content;
	}
	else if (new_content)
		ft_lstadd_back(&(data->env), ft_lstnew(new_content));
}

int	export_cmd(t_cmd *cmd, t_data *data)
{
	int	i;
	int	j;
	int	error_flag;

	i = 0;
	error_flag = 0;
	while (cmd->cmd[++i])
	{
		j = 0;
		while (cmd->cmd[i][j] && is_valid_var_name_export(cmd->cmd[i], j))
			j++;
		if ((cmd->cmd[i][j] == '=' || !ft_memcmp(cmd->cmd[i] + j, "+=", 2))
			&& j != 0)
			update_or_add_env_var(data, cmd->cmd[i], j, 0);
		else if (cmd->cmd[i][j] || j == 0)
		{
			handle_export_error(cmd->cmd[i]);
			error_flag = 1;
		}
		else if (!(cmd->cmd[i][j]))
			add_env_var_if_missing(data, cmd->cmd[i]);
	}
	if (cmd->cmd[1] == NULL)
		print_exported_env(cmd, data);
	return (error_flag);
}
