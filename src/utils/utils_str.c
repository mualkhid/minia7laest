/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:52:22 by mualkhid          #+#    #+#             */
/*   Updated: 2024/08/20 18:52:24 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_it_in_str(char *str, char c)
{
	if (str)
	{
		while (*str)
		{
			if (*str == c)
				return (1);
			str++;
		}
	}
	return (0);
}

int	wildcards_strcmp(char *s1, char *s2)
{
	char	c1;
	char	c2;

	c1 = 0;
	c2 = 0;
	while (c1 == c2 && *s1 && *s2)
	{
		c1 = s1[0];
		c2 = s2[0];
		if (c1 >= 'A' && c1 <= 'Z')
			c1 += 32;
		if (c2 >= 'A' && c2 <= 'Z')
			c2 += 32;
		s1++;
		s2++;
	}
	if (c1 == c2)
		return (s1[0] - s2[0]);
	return (c1 - c2);
}

int	export_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	only_space(char *string)
{
	int	i;

	i = -1;
	while (string[++i])
	{
		if (string[i] != ' ')
			return (0);
	}
	return (1);
}

char	*get_str(const char *s, size_t *i, int j)
{
	char	*cp;

	j = *i;
	cp = malloc(j + 1);
	memcpy(cp, s, j);
	cp[j] = 0;
	return (cp);
}
