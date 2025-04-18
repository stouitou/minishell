/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_in_parent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:36:20 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/11 10:29:04 by stouitou         ###   ########.fr       */
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
		ft_fprintf(2, "exit: %s: numeric argument required\n", arg);
		return (2);
	}
	return (0);
}

static bool	wrong_argument(t_entry *entry, t_exe *exe, char **cmd, int *status)
{
	if (cmd[1])
	{
		*status = check_cmd_content(cmd[1]);
		if (*status)
		{
			entry->status = *status;
			free_exe(exe);
			return (true);
		}
		if (cmd[2])
		{
			entry->exit = false;
			ft_fprintf(2, "exit: too many arguments\n");
			entry->status = 1;
			free_exe(exe);
			return (true);
		}
	}
	return (false);
}

bool	handle_exit_in_parent(t_entry *entry, t_exe *exe, char **cmd)
{
	int		exit_status;

	if (!get_files_fd_for_builtin(exe, exe->files, "exit"))
	{
		free_exe(exe);
		entry->status = 1;
		return (true);
	}
	write(2, "exit\n", 5);
	if (g_sig)
		exit_status = g_sig;
	else
		exit_status = entry->prev_status;
	entry->exit = true;
	if (cmd[1])
	{
		if (wrong_argument(entry, exe, cmd, &exit_status))
			return (true);
		exit_status = get_exit_status(cmd[1]);
	}
	free_exe(exe);
	entry->status = exit_status;
	return (true);
}
