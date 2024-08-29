/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:54:30 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/20 18:54:31 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	start_check(char *sequence, char **dir_name, char **s, int i)
{
	int	len_sequence;

	if (!sequence || sequence[0] == '\0')
	{
		free(sequence);
		return (1);
	}
	len_sequence = ft_strlen(sequence);
	if (ft_memcmp(sequence, *dir_name, len_sequence))
	{
		free(sequence);
		return (0);
	}
	free(sequence);
	*dir_name = *dir_name + len_sequence;
	*s = *s + i + 1;
	return (1);
}

int	end_check(char *sequence, char *dir_name)
{
	int	len;
	int	len_sequence;

	if (!sequence || sequence[0] == '\0')
	{
		free(sequence);
		return (1);
	}
	len = ft_strlen(dir_name);
	len_sequence = ft_strlen(sequence);
	if (len < len_sequence)
	{
		free(sequence);
		return (0);
	}
	if (ft_memcmp(sequence, dir_name + len - len_sequence, len_sequence + 1))
	{
		free(sequence);
		return (0);
	}
	free(sequence);
	return (1);
}

int	check_first_wildards(char **s, char **dir_name, t_data *data)
{
	int		i;
	int		quote;
	char	*sub;

	i = 0;
	quote = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '*' && !quote)
		{
			sub = exec_transformation(ft_substr(*s, 0, i), data);
			if (!start_check(sub, dir_name, s, i))
				return (0);
			else
				return (1);
		}
		else if ((*s)[i] == '\'' && quote != 2)
			quote = (quote + 1) % 2;
		else if ((*s)[i] == '\"' && quote != 1)
			quote = (quote + 2) % 4;
		i++;
	}
	return (1);
}

int	check_sequence(char *sequence, char **dir_name)
{
	int		len;
	char	*search;

	if (!sequence || sequence[0] == '\0')
	{
		free(sequence);
		return (1);
	}
	len = ft_strlen(*dir_name);
	search = ft_strnstr(*dir_name, sequence, len);
	if (search == NULL)
	{
		free(sequence);
		return (0);
	}
	*dir_name = search + ft_strlen(sequence);
	free(sequence);
	return (1);
}
