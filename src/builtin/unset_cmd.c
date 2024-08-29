/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:56:21 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 13:49:25 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_var_name_unset(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if ((i == 0 && !ft_isalpha(name[i]) && name[i] != '_')
			|| (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_'))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(name, 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			return (0);
		}
	}
	return (1);
}

static void	delete_lst(t_list **env_lst)
{
	t_list	*node;

	node = *env_lst;
	(*env_lst) = node->next;
	ft_lstdelone(node, &free);
}

int	unset_cmd(t_cmd *cmd, t_data *data)
{
	int		i;
	int		ret;
	t_list	**lst;

	i = 0;
	ret = 0;
	while (cmd->cmd[++i])
	{
		if (!is_valid_var_name_unset(cmd->cmd[i]))
			ret = 1;
		else
		{
			lst = &(data->env);
			while (*lst)
			{
				if (!ft_strncmp(cmd->cmd[i], (char *)(*lst)->content,
					ft_strlen(cmd->cmd[i])))
					delete_lst(lst);
				else
					lst = &((*lst)->next);
			}
		}
	}
	return (ret);
}
