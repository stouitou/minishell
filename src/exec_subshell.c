/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:09:17 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/06 14:00:59 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_subshell(t_exe *exe, int i, int prev_status)
{
	char		*command;
	char		*msg;
	char		*data;
	int			status;

	command = NULL;
	msg = exe->error.msg;
	data = exe->error.data;
	status = exe->error.status;
	if (!get_files_fd(exe, exe->files))
		free_subshell_and_exit(exe, msg, data, status);
	if (!is_builtin(exe->cmd[0]))
	{
		command = find_cmd(exe, exe->cmd);
		if (!command)
			free_subshell_and_exit(exe, NULL, NULL, 0);
	}
	execute_command(exe, command, i, prev_status);
}
