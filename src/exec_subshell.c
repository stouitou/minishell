/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:09:17 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/30 09:08:37 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_subshell(t_exe *exe, int i, int prev_status)
{
	char		*command;

	command = NULL;
	if (!get_files_fd(exe, exe->files))
		free_subshell_and_exit(exe, exe->error.msg, exe->error.data, exe->error.status);
	if (!is_builtin(exe->cmd[0]))
	{
		command = find_cmd(exe, exe->cmd);
		if (!command)
			free_subshell_and_exit(exe, NULL, NULL, 0);
	}
	execute_command(exe, command, i, prev_status);
}
