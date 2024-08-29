/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:18:22 by mualkhid          #+#    #+#             */
/*   Updated: 2023/12/11 13:11:22 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*sc;
	char	*dest;

	sc = (char *)src;
	dest = (char *)dst;
	if (sc < dest)
	{
		while (n)
		{
			dest[n - 1] = sc[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest, sc, n);
	return (dst);
}
