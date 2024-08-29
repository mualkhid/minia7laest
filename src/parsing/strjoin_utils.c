/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:53:40 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/28 23:44:40 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	total_length(int size, char **strs)
{
	int	i;
	int	total_len;

	i = -1;
	total_len = 0;
	while (++i < size)
		total_len += ft_strlen(strs[i]);
	return (total_len);
}

static int	append_str(char *dest, char *src, int n)
{
	int	i;

	i = -1;
	while (src[++i])
		dest[n + i] = src[i];
	return (i);
}

char	*join_strings(int size, char **strs, char *sep)
{
	int		total_len;
	char	*final_string;
	int		i;
	int		i_total;

	if (size <= 0)
		total_len = 0;
	else
		total_len = total_length(size, strs) + ft_strlen(sep) * (size - 1);
	final_string = malloc((total_len + 1) * sizeof(char));
	if (final_string == NULL)
		return (NULL);
	i = 0;
	i_total = 0;
	while (size > 0 && i < size)
	{
		i_total += append_str(final_string, strs[i], i_total);
		i++;
		if (i < size)
			i_total += append_str(final_string, sep, i_total);
	}
	final_string[i_total] = '\0';
	return (final_string);
}
