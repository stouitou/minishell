/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:28:18 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/23 13:14:57 by stouitou         ###   ########.fr       */
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
		// entry->exit = true;
		init_error(exe, "numeric argument required", arg, 2);
		exit_builtin(exe, "exit");
	}
	return (0);
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

static int	check_exit_status(t_exe *exe, char *arg)
{
	unsigned long	res;
	int				i;

	i = iterate(arg);
	res = 0;
	if (beyond_limits(arg + i))
	{
		// entry->exit = true;
		init_error(exe, "numeric argument required", arg, 2);
		exit_builtin(exe, "exit");
	}
	while (ft_isdigit(arg[i]))
	{
		res = res * 10 + arg[i] - '0';
		i++;
	}
	if (res > LONG_MAX)
	{
		// entry->exit = true;
		init_error(exe, "numeric argument required", arg, 2);
		exit_builtin(exe, "exit");
	}
	return (res % (unsigned)256);
}

void	handle_exit(t_exe *exe, char **cmd)
{
	int	exit_status;
	int	ac;

	if (!get_files_fd_for_exit(exe, exe->files))
		exit (1);
	exit_status = 0;
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
	exit (exit_status);
}
