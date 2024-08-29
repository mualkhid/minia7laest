/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:52:14 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/20 18:52:17 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_digit(char *content)
{
	int	i;

	i = -1;
	if (content[0] == '-')
		i++;
	while (content[++i])
	{
		if (!ft_isdigit(content[i]))
			return (0);
	}
	return (1);
}

static int	ft_shlvl_atoi(char *str)
{
	int	i;
	int	n;

	if (!is_digit(str))
		return (1);
	if (str[0] == '-')
		return (0);
	n = 0;
	i = 0;
	while (ft_isdigit(str[i]) && n < 999)
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '\0' && n < 999)
		return (n + 1);
	ft_putendl_fd("the level is too high to be true", 1);
	return (1);
}

static char	*new_shlvl(char *content)
{
	int		value;
	char	*temp;
	char	*new_content;

	value = ft_shlvl_atoi(content);
	temp = ft_itoa(value);
	new_content = ft_strjoin("SHLVL=", temp);
	free(temp);
	return (new_content);
}

void	shlvl(t_data *data)
{
	t_list	*lst;
	char	*new_content;

	lst = data->env;
	while (lst)
	{
		if (!ft_strncmp("SHLVL", (char *)lst->content, 5)
			&& ft_strlen((char *)lst->content) >= 5
			&& ((char *)lst->content)[5] == '=')
		{
			new_content = new_shlvl(lst->content + 6);
			if (new_content == NULL)
				return ;
			free(lst->content);
			lst->content = new_content;
			return ;
		}
		else
			lst = lst->next;
	}
	new_content = ft_strdup("SHLVL=1");
	if (new_content)
		ft_lstadd_back(&data->env, ft_lstnew(new_content));
}
