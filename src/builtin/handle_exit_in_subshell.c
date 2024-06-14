/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_in_subshell.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:28:18 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 12:58:36 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmd_content(t_exe *exe, char *arg)
{
	int	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i] != '\0')
	{
		init_error(exe, "numeric argument required", arg, 2);
		exit_builtin(exe, "exit");
	}
	return (0);
}

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

	if (res <= LONG_MAX)
		return (0);
	mask = 1UL << 63;
	if (res & mask)
	{
		if (sign > 0)
			return (1);
		if (res & ~mask)
			return (1);
	}
	return (0);
}

static int	check_exit_status(t_exe *exe, char *arg)
{
	unsigned long	res;
	int				i;
	int				sign;

	sign = 1;
	i = iterate(arg, &sign);
	res = 0;
	if (arg_too_long(arg + i))
	{
		init_error(exe, "numeric argument required", arg, 2);
		exit_builtin(exe, "exit");
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

int	handle_exit_in_subshell(t_exe *exe, char **cmd, int prev_status)
{
	int	exit_status;
	int	ac;

	if (!get_files_fd_for_builtin(exe, exe->files, "exit"))
		return (1);
	exit_status = prev_status;
	ac = ft_str_array_len(cmd);
	if (ac > 1)
	{
		exit_status = check_cmd_content(exe, cmd[1]);
		if (!exit_status && ac > 2)
		{
			init_error(exe, "too many arguments", NULL, 2);
			exit_builtin(exe, "exit");
		}
		exit_status = check_exit_status(exe, cmd[1]);
	}
	return (exit_status);
}
