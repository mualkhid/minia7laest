/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:16:10 by mualkhid          #+#    #+#             */
/*   Updated: 2023/12/11 22:58:37 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	islongneg(long num, char c, int sign)
{
	if (sign == -1 && ((num > LONG_MAX / 10) || (num == LONG_MAX / 10 && (c
					- '0') >= 8)))
		return (-1);
	else
		return (0);
}

static int	islongpos(long num, char c, int sign)
{
	if (sign == 1 && (num > (LONG_MAX / 10) || (num == LONG_MAX / 10 && (c
					- '0') >= 7)))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned long long	result;
	long				sign;
	size_t				i;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while ((nptr[i] != '\0') && ft_isdigit(nptr[i]))
	{
		if (islongneg(result, nptr[i], sign))
			return (0);
		else if (islongpos(result, nptr[i], sign))
			return (-1);
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}
