/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_aoss.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:52:28 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/20 18:52:31 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**convert_to_aos(t_list *lst)
{
	int		i;
	char	**strs;

	strs = malloc(sizeof(char *) * (ft_cmd_len(lst) + 1));
	if (!strs)
		return (0);
	i = 0;
	while (lst)
	{
		if (((char *)lst->content) != NULL)
		{
			strs[i++] = ft_strdup((char *)lst->content);
			if (!strs[i - 1])
			{
				free_aos(strs);
				return (0);
			}
		}
		lst = lst->next;
	}
	strs[i] = 0;
	return (strs);
}

int	aos_len(char **aos)
{
	int	size;

	if (!aos)
		return (0);
	size = 0;
	while (aos[size])
		size++;
	return (size);
}

void	free_aos(char **aos)
{
	int	i;

	if (!aos)
		return ;
	i = 0;
	while (aos[i])
	{
		free(aos[i]);
		i++;
	}
	free(aos);
}

void	sort_aos(char **aos, int size, int(f)(char *, char *))
{
	int		i;
	int		j;
	char	*str_temp;

	if (size <= 1)
		return ;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (f(aos[i], aos[j]) < 0)
			{
				str_temp = &(aos[i][0]);
				aos[i] = &(aos[j][0]);
				aos[j] = str_temp;
			}
			j++;
		}
		i++;
	}
}
