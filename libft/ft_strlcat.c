/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:20:12 by mualkhid          #+#    #+#             */
/*   Updated: 2023/12/11 17:11:34 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(dest) >= size)
		return (size + ft_strlen(src));
	if (size)
	{
		while (dest[j])
			j++;
		while (((i + j) < size - 1) && src[i])
		{
			dest[i + j] = src[i];
			i++;
		}
		dest[i + j] = '\0';
	}
	while (src[i])
		i++;
	return (i + j);
}
