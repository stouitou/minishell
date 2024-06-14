/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:06:21 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 16:05:14 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_when_needed(t_exe *exe, int i)
{
	if (i % 2 == 0)
	{
		if (i)
			init_dup(exe, exe->pipe_fd2[0], STDIN_FILENO);
		if (i < (exe->blocks - 1))
			init_dup(exe, exe->pipe_fd1[1], STDOUT_FILENO);
	}
	if ((i % 2 != 0))
	{
		init_dup(exe, exe->pipe_fd1[0], STDIN_FILENO);
		if (i < exe->blocks - 1)
			init_dup(exe, exe->pipe_fd2[1], STDOUT_FILENO);
	}
	if (exe->io_fd[0] != -1)
		init_dup(exe, exe->io_fd[0], STDIN_FILENO);
	if (exe->io_fd[1] != -1)
		init_dup(exe, exe->io_fd[1], STDOUT_FILENO);
}

void	execute_command(t_exe *exe, char *command, int i, int prev_status)
{
	char	**env;

	dup_when_needed(exe, i);
	close_all_fd(exe);
	env = upd_env(exe, exe->env);
	if (is_builtin(exe->cmd[0]))
		handle_builtin_in_subshell(exe, exe->cmd[0], prev_status);
	else
		execve(command, exe->cmd, env);
	ft_free_str_array(env);
	free_subshell_and_exit(exe, strerror(errno), "execve", EXIT_FAILURE);
}
