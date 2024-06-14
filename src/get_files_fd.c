/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:58:09 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/12 11:33:47 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_infile_fd(t_exe *exe, char *file)
{
	if (exe->io_fd[0] != -1)
		close (exe->io_fd[0]);
	exe->io_fd[0] = open(file, O_RDONLY);
	if (exe->io_fd[0] == -1)
	{
		init_error(exe, strerror(errno), file, EXIT_FAILURE);
		return ;
	}
}

static void	get_outfile_fd(t_exe *exe, char *file)
{
	if (exe->io_fd[1] != -1)
		close (exe->io_fd[1]);
	exe->io_fd[1] = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00666);
	if (exe->io_fd[1] == -1)
	{
		init_error(exe, strerror(errno), file, EXIT_FAILURE);
		return ;
	}
}

static void	get_app_outfile_fd(t_exe *exe, char *file)
{
	if (exe->io_fd[1] != -1)
		close (exe->io_fd[1]);
	exe->io_fd[1] = open(file, O_CREAT | O_WRONLY | O_APPEND, 00666);
	if (exe->io_fd[1] == -1)
	{
		init_error(exe, strerror(errno), file, EXIT_FAILURE);
		return ;
	}
}

int	get_files_fd(t_exe *exe, t_files *file)
{
	if (!file)
		return (1);
	while (file)
	{
		if (file->category == INFILE || file->category == DELIMITER)
		{
			get_infile_fd(exe, file->content);
			if (exe->io_fd[0] == -1)
				return (0);
		}
		if (file->category == OUTFILE)
		{
			get_outfile_fd(exe, file->content);
			if (exe->io_fd[1] == -1)
				return (0);
		}
		if (file->category == APP_OUTFILE)
		{
			get_app_outfile_fd(exe, file->content);
			if (exe->io_fd[1] == -1)
				return (0);
		}
		file = file->next;
	}
	return (1);
}
