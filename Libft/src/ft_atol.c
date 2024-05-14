/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:33:04 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 11:15:54 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	adapt_res(int *sign)
{
	long	res;

	if (*sign == 1)
		res = LONG_MAX;
	if (*sign == -1)
	{
		res = LONG_MIN;
		*sign = 1;
	}
	return (res);
}

static bool	beyond_limits(const char *nb)
{
	int	i;

	i = 0;
	while (ft_isdigit(nb[i]))
		i++;
	if (i > 19)
		return (true);
	return (false);
}

static int	iterate(const char *nb, int *sign)
{
	int	i;

	i = 0;
	while (ft_isspace(nb[i]))
		i++;
	if (nb[i] == '+' || nb[i] == '-')
	{
		if (nb[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

long	ft_atol(const char *nptr)
{
	unsigned long	res;
	int				sign;
	int				i;

	if (nptr == NULL)
		return (0);
	res = 0;
	sign = 1;
	i = iterate(nptr, &sign);
	if (beyond_limits(nptr + i))
	{
		if (sign == 1)
			return (LONG_MAX);
		if (sign == -1)
			return (LONG_MIN);
	}
	while (ft_isdigit(nptr[i]))
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	if (res > LONG_MAX)
		res = adapt_res(&sign);
	return ((long)res * sign);
}
