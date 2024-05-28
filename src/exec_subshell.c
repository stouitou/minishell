/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:09:17 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 09:38:05 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	get_files_fd(t_exe *exe, t_files *file)
{
	if (!file)
		return (1);
	while (file)
	{
		if (file->category == INFILE || file->category == DELIMITER)
		{
			if (exe->io_fd[0] != -1)
				close (exe->io_fd[0]);
			// if (access(file->content, F_OK | R_OK) == -1)
			// {
			// 	init_error(exe, strerror(errno), file->content, EXIT_FAILURE);
			// 	return (0);
			// }
			exe->io_fd[0] = open(file->content, O_RDONLY);
			if (exe->io_fd[0] == -1)
			{
				init_error(exe, strerror(errno), file->content, EXIT_FAILURE);
				return (0);
			}
		}
		if (file->category == OUTFILE)
		{
			if (exe->io_fd[1] != -1)
				close (exe->io_fd[1]);
			exe->io_fd[1] = open(file->content, O_CREAT | O_WRONLY | O_TRUNC, 00666);
			if (exe->io_fd[1] == -1)
			{
				init_error(exe, strerror(errno), file->content, EXIT_FAILURE);
				return (0);
			}
		}
		if (file->category == APP_OUTFILE)
		{
			if (exe->io_fd[1] != -1)
				close (exe->io_fd[1]);
			exe->io_fd[1] = open(file->content, O_CREAT | O_WRONLY | O_APPEND, 00666);
			if (exe->io_fd[1] == -1)
			{
				init_error(exe, strerror(errno), file->content, EXIT_FAILURE);
				return (0);
			}
		}
		file = file->next;
	}
	return (1);
}

static void	execute_command(t_exe *exe, char *command, int i, int prev_status)
{
	char	**env;
	
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
	close_all_fd(exe);
	env = upd_env(exe, exe->env);
	if (is_builtin(exe->cmd[0]))
		handle_builtin(exe, exe->cmd[0], prev_status);
	// print_env(env);
	execve(command, exe->cmd, env);
	init_error(exe, strerror(errno), "execve", EXIT_FAILURE);
	free_subshell_and_exit(exe);
}

void	exec_subshell(t_exe *exe, int i, int prev_status)
{
	char		*command;

	command = NULL;
	if (!get_files_fd(exe, exe->files))
		free_subshell_and_exit(exe);
	if (!is_builtin(exe->cmd[0]))
	{
		command = find_cmd(exe, exe->cmd);
		if (!command)
		{
			init_error(exe, NULL, NULL, 0);
			free_subshell_and_exit(exe);
		}
	}
	execute_command(exe, command, i, prev_status);
}
