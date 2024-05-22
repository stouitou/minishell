/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_in_parent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:36:20 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/22 16:19:39 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cmd_content(char *arg)
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
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
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

static int	check_exit_status(char *arg)
{
	unsigned long	res;
	int				i;

	i = iterate(arg);
	res = 0;
	if (beyond_limits(arg + i))
	{
		// entry->exit = true;
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
		// init_error(exe, "numeric argument required", arg, 2);
		// exit_builtin(exe, "exit");
	}
	while (ft_isdigit(arg[i]))
	{
		res = res * 10 + arg[i] - '0';
		i++;
	}
	if (res > LONG_MAX)
	{
		// entry->exit = true;
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
		// init_error(exe, "numeric argument required", arg, 2);
		// exit_builtin(exe, "exit");
	}
	return (res % (unsigned)256);
}

int	handle_exit_in_parent(t_entry *entry, t_exe *exe, char **cmd)
{
	int		exit_status;
	int		ac;

	if (!cmd || exe->blocks > 1 || ft_strcmp(cmd[0], "exit") != 0)
		return (0);
	if (!get_files_fd_for_exit(exe, exe->files))
	{
		free_exe(exe);
		entry->status = 1;
		return (1);
	}
	write(2, "exit\n", 5);
	exit_status = 0;
	entry->exit = true;
	ac = ft_str_array_len(cmd);
	if (ac > 1)
	{
		exit_status = check_cmd_content(cmd[1]);
		if (exit_status)
		{
			entry->status = exit_status;
			free_exe(exe);
			return (1);
		}
		if (!exit_status && ac > 2)
		{
			entry->exit = false;
			ft_fprintf(2, "exit: too many arguments\n");
			entry->status = 1;
			free_exe(exe);
			return (1);
		}
		exit_status = check_exit_status(cmd[1]);
	}
	free_exe(exe);
	entry->status = exit_status;
	// ft_printf("in handle exit, status = %d\n", exit_status);
	return (1);
}
