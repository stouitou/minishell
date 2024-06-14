/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:59:21 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 12:48:44 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	arg_too_long(const char *nb)
{
	int	i;

	i = 0;
	while (ft_isdigit(nb[i]))
		i++;
	if (i > 19)
		return (true);
	return (false);
}

static int	iterate(char *nb, int *sign)
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

static int	is_beyond_limits(unsigned long res, int sign)
{
	unsigned long	mask;

	mask = 1UL << 63;
	if (res <= LONG_MAX)
		return (0);
	if (res & (mask))
	{
		if (sign > 0)
			return (1);
		if (res & (~(mask)))
			return (1);
	}
	return (0);
}

int	get_exit_status(char *arg)
{
	unsigned long	res;
	int				i;
	int				sign;

	sign = 1;
	i = iterate(arg, &sign);
	res = 0;
	if (arg_too_long(arg + i))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
	}
	while (ft_isdigit(arg[i]))
	{
		res = res * 10 + arg[i] - '0';
		i++;
	}
	if (is_beyond_limits(res, sign))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
	}
	if (sign < 0)
		res = 256 - (res % 256);
	return (res % (unsigned)256);
}
