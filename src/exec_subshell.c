/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:09:17 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/13 15:45:42 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_infile_fd(t_exe *exe)
{
	int	fd;
	int	i;

	if (exe->infile[0] == NULL)
		return (-1);
	i = 0;
	while (exe->infile[i])
	{
		// ft_printf("in get_infile fd, exe->infile[%d] = %s\n", i, exe->infile[i]);
		if (access(exe->infile[i], F_OK | R_OK) == -1)
		{
			init_error(exe, strerror(errno), exe->infile[i], EXIT_FAILURE);
			free_subshell_and_exit(exe);
		}
		fd = open(exe->infile[i], O_RDONLY);
		if (fd == -1)
		{
			init_error(exe, strerror(errno), exe->infile[i], EXIT_FAILURE);
			free_subshell_and_exit(exe);
		}
		i++;
		if (exe->infile[i])
			close(fd);
	}
	// ft_printf("in get_infile fd, fd= %d\n", fd);
	return (fd);
}

static int	get_outfile_fd(t_exe *exe)
{
	int	fd;
	int	i;

	if (exe->outfile[0] == NULL)
		return (-1);
	i = 0;
	while (exe->outfile[i])
	{
		if (access(exe->outfile[i], F_OK) == 0)
		{
			if (access(exe->outfile[i], W_OK) == -1)
			{
				init_error(exe, strerror(errno), exe->outfile[i], EXIT_FAILURE);
				free_subshell_and_exit(exe);
			}
		}
		fd = open(exe->outfile[i], O_CREAT | O_WRONLY | O_TRUNC, 00666);
		if (fd == -1)
		{
			init_error(exe, strerror(errno), exe->outfile[i], EXIT_FAILURE);
			free_subshell_and_exit(exe);
		}
		i++;
		if (exe->outfile[i])
			close(fd);
	}
	return (fd);
}

static int	get_app_outfile_fd(t_exe *exe)
{
	int	fd;
	int	i;

	if (exe->app_outfile[0] == NULL)
		return (-1);
	i = 0;
	while (exe->app_outfile[i])
	{
		if (access(exe->app_outfile[i], F_OK) == 0)
		{
			if (access(exe->app_outfile[i], W_OK) == -1)
			{
				init_error(exe, strerror(errno), exe->app_outfile[i], EXIT_FAILURE);
				free_subshell_and_exit(exe);
			}
		}
		fd = open(exe->app_outfile[i], O_CREAT | O_WRONLY | O_APPEND, 00666);
		if (fd == -1)
		{
			init_error(exe, strerror(errno), exe->app_outfile[i], EXIT_FAILURE);
			free_subshell_and_exit(exe);
		}
		i++;
		if (exe->app_outfile[i])
			close(fd);
	}
	return (fd);
}

static void	execute_command(t_exe *exe, char *command, int i)
{
	if (exe->ioda_fd[0] != -1)
		init_dup(exe, exe->ioda_fd[0], STDIN_FILENO);
	if (exe->ioda_fd[1] != -1)
		init_dup(exe, exe->ioda_fd[1], STDOUT_FILENO);
	if (exe->ioda_fd[3] != -1)
		init_dup(exe, exe->ioda_fd[3], STDOUT_FILENO);
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
	close_all_fd(exe);
	execve(command, exe->cmd, exe->env);
	init_error(exe, strerror(errno), "execve", EXIT_FAILURE);
	free_subshell_and_exit(exe);
}

void	exec_subshell(t_entry *entry, t_exe *exe, int i)
{
	char		*command;

	(void)entry;
	if (exe->infile)
		exe->ioda_fd[0] = get_infile_fd(exe);
	if (exe->outfile)
		exe->ioda_fd[1] = get_outfile_fd(exe);
	if (exe->app_outfile)
		exe->ioda_fd[3] = get_app_outfile_fd(exe);
	command = find_cmd(exe, exe->cmd);
	if (!command)
	{
		init_error(exe, NULL, NULL, 0);
		free_subshell_and_exit(exe);
	}
	// print_exe(entry, entry->token, exe, i);
	execute_command(exe, command, i);
}
