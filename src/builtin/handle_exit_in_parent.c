/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_in_parent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:36:20 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 11:07:24 by stouitou         ###   ########.fr       */
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

int	handle_exit_in_parent(t_entry *entry, t_exe *exe, char **cmd)
{
	int		exit_status;

	if (!cmd || exe->blocks > 1 || ft_strcmp(cmd[0], "exit") != 0)
		return (0);
	if (!get_files_fd_for_builtin(exe, exe->files, "exit"))
	{
		free_exe(exe);
		entry->status = 1;
		return (1);
	}
	write(2, "exit\n", 5);
	exit_status = entry->prev_status;
	entry->exit = true;
	if (cmd[1])
	{
		if (wrong_argument(entry, exe, cmd, &exit_status))
			return (1);
		exit_status = get_exit_status(cmd[1]);
	}
	free_exe(exe);
	entry->status = exit_status;
	return (1);
}
