/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:19:20 by mualkhid          #+#    #+#             */
/*   Updated: 2023/12/11 20:41:51 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**memfree(char **split, int i)
{
	int	j;

	j = i;
	while (j >= 0)
	{
		if (split[j] == NULL)
		{
			while (i >= 0)
			{
				if (split[i] != NULL)
					free(split[i]);
				i--;
			}
			free(split);
			return (NULL);
		}
		j--;
	}
	return (split);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	word_tracker;

	i = 0;
	word_tracker = 0;
	while (*str)
	{
		if (*str != c && word_tracker == 0)
		{
			word_tracker = 1;
			i++;
		}
		else if (*str == c)
			word_tracker = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	int		j;
	int		current_position;
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	i = 0;
	j = 0;
	current_position = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && current_position < 0)
			current_position = i;
		else if ((s[i] == c || i == ft_strlen(s)) && current_position >= 0)
		{
			split[j++] = word_dup(s, current_position, i);
			current_position = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (memfree(split, j - 1));
}
