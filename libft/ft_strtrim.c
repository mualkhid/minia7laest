/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:21:35 by mualkhid          #+#    #+#             */
/*   Updated: 2023/12/11 18:29:05 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_for_char(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	lead;
	size_t	trail;

	lead = 0;
	while (s1[lead] && check_for_char(s1[lead], set))
		lead++;
	trail = ft_strlen(s1);
	while (trail > lead && check_for_char(s1[trail - 1], set))
		trail--;
	str = (char *)malloc(sizeof(*s1) * (trail - lead + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (lead < trail)
		str[i++] = s1[lead++];
	str[i] = 0;
	return (str);
}
