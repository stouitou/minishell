/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:59:21 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/04 16:52:46 by poriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	iterate(char *nb)
{
	int	i;

	i = 0;
	while (ft_isspace(nb[i]))
		i++;
	if (nb[i] == '+' || nb[i] == '-')
		i++;
	return (i);
}

int	get_exit_status(char *arg)
{
	unsigned long	res;
	int				i;

	i = iterate(arg);
	res = 0;
	if (beyond_limits(arg + i))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
	}
	while (ft_isdigit(arg[i]))
	{
		res = res * 10 + arg[i] - '0';
		i++;
	}
	if (res > LONG_MAX)
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
	}
	return (res % (unsigned)256);
}
