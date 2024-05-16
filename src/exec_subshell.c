/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:09:17 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 17:37:05 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_outfile(t_outfile *outfile)
// {
// 	if (!outfile)
// 		return ;
// 	while (outfile)
// 	{
// 		ft_printf("outfile = %s\n", outfile->content);
// 		outfile = outfile->next;
// 	}
// }

static int	get_infile_fd(t_exe *exe)
{
	int	fd;
	int	i;

	if (exe->infile[0] == NULL)
		return (-1);
	i = 0;
	while (exe->infile[i])
	{
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
	return (fd);
}

static int	get_outfile_fd(t_exe *exe, t_outfile *outfile)
{
	int	fd;

	// print_outfile(outfile);
	if (!outfile)
		return (-1);
	while (outfile)
	{
		if (access(outfile->content, F_OK) == 0)
		{
			if (access(outfile->content, W_OK) == -1)
			{
				init_error(exe, strerror(errno), outfile->content, EXIT_FAILURE);
				free_subshell_and_exit(exe);
			}
		}
		if (!outfile->append)
		{
			// ft_printf("here in NOT append\n");
			fd = open(outfile->content, O_CREAT | O_WRONLY | O_TRUNC, 00666);
			if (fd == -1)
			{
				init_error(exe, strerror(errno), outfile->content, EXIT_FAILURE);
				free_subshell_and_exit(exe);
			}
		}
		else
		{
			// ft_printf("here in append\n");
			fd = open(outfile->content, O_CREAT | O_WRONLY | O_APPEND, 00666);
			if (fd == -1)
			{
				init_error(exe, strerror(errno), outfile->content, EXIT_FAILURE);
				free_subshell_and_exit(exe);
			}
		}
		outfile = outfile->next;
		if (outfile)
			close(fd);
	}
	// ft_printf("fd = %d\n", fd);
	return (fd);
}

static void	execute_command(t_entry *entry, t_exe *exe, char *command, int i)
{
	(void)entry;
	// print_exe(entry, entry->token, exe, i);
	if (exe->iod_fd[0] != -1)
		init_dup(exe, exe->iod_fd[0], STDIN_FILENO);
	if (exe->iod_fd[1] != -1)
		init_dup(exe, exe->iod_fd[1], STDOUT_FILENO);
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
	// ft_fprintf(2, "Executing %s with %s and %s, infile: %d, outfile: %d\n", command, exe->cmd[0], exe->cmd[1], exe->iod_fd[0], exe->iod_fd[1]);
	execve(command, exe->cmd, exe->env);
	init_error(exe, strerror(errno), "execve", EXIT_FAILURE);
	free_subshell_and_exit(exe);
}

void	exec_subshell(t_entry *entry, t_exe *exe, int i)
{
	char		*command;

	if (exe->infile)
		exe->iod_fd[0] = get_infile_fd(exe);
	if (exe->outfile)
		exe->iod_fd[1] = get_outfile_fd(exe, exe->outfile);
	if (exe->delimiter)
		go_heredoc(exe, exe->delimiter);
	command = find_cmd(exe, exe->cmd);
	if (!command)
	{
		init_error(exe, NULL, NULL, 0);
		free_subshell_and_exit(exe);
	}
	execute_command(entry, exe, command, i);
}
