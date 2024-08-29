/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:20:31 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/29 12:59:50 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_free(char *ss)
{
	free(ss);
	return (0);
}

static int	is_exec_transformationation_needed(char **ss, int *i, t_data *data,
		int *not_null)
{
	if ((*ss)[*i] == '"' && ++(*not_null))
	{
		if (parse_double_quotes(ss, i, data))
			return (2);
	}
	else if ((*ss)[*i] == '\'' && ++(*not_null))
	{
		if (parse_single_quotes(ss, i))
			return (2);
	}
	else if ((*ss)[*i] == '$')
		replace_var(ss, i, data);
	else
		return (0);
	return (1);
}

char	*exec_transformation(char *original, t_data *data)
{
	int		i;
	int		j;
	char	*ss;
	int		not_null;

	i = 0;
	not_null = 0;
	ss = original;
	if (!ss)
		return (0);
	while (ss[i])
	{
		j = is_exec_transformationation_needed(&ss, &i, data, &not_null);
		if (j == 2)
			return (ft_free(ss));
		else if (j == 0)
			i++;
	}
	if (ss[0] == '\0' && !not_null)
		return (ft_free(ss));
	return (ss);
}
