/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files_fd_for_builtin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:37:18 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 16:02:41 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	open_infile(t_exe *exe, char *file, char *builtin)
{
	if (exe->io_fd[0] != -1)
		close (exe->io_fd[0]);
	// if (access(file, F_OK | R_OK) == -1)
	// {
	// 	ft_fprintf(2, "%s: %s\n", file, strerror(errno));
	// 	init_error(exe, strerror(errno), file, EXIT_FAILURE);
	// 	return (false);
	// }
	exe->io_fd[0] = open(file, O_RDONLY);
	if (exe->io_fd[0] == -1)
	{
		ft_fprintf(2, "%s: %s\n", builtin, strerror(errno));
		init_error(exe, strerror(errno), file, EXIT_FAILURE);
		return (false);
	}
	return (true);
}

static bool	open_outfile(t_exe *exe, char *file, char *builtin)
{
	if (exe->io_fd[1] != -1)
		close (exe->io_fd[1]);
	// if (access(file, F_OK) == 0)
	// {
	// 	if (access(file, W_OK) == -1)
	// 	{
	// 		ft_fprintf(2, "%s: %s\n", file, strerror(errno));
	// 		init_error(exe, strerror(errno), file, EXIT_FAILURE);
	// 		return (false);
	// 	}
	// }
	exe->io_fd[1] = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00666);
	if (exe->io_fd[1] == -1)
	{
		ft_fprintf(2, "%s: %s\n", builtin, strerror(errno));
		init_error(exe, strerror(errno), file, EXIT_FAILURE);
		return (false);
	}
	return (true);
}

static bool	open_app_outfile(t_exe *exe, char *file, char *builtin)
{
	if (exe->io_fd[1] != -1)
		close (exe->io_fd[1]);
	// if (access(file, F_OK) == 0)
	// {
	// 	if (access(file, W_OK) == -1)
	// 	{
	// 		ft_fprintf(2, "%s: %s\n", file, strerror(errno));
	// 		init_error(exe, strerror(errno), file, EXIT_FAILURE);
	// 		return (false);
	// 	}
	// }
	exe->io_fd[1] = open(file, O_CREAT | O_WRONLY | O_APPEND, 00666);
	if (exe->io_fd[1] == -1)
	{
		ft_fprintf(2, "%s: %s\n", builtin, strerror(errno));
		init_error(exe, strerror(errno), file, EXIT_FAILURE);
		return (false);
	}
	return (true);
}

int	get_files_fd_for_builtin(t_exe *exe, t_files *file, char *builtin)
{
	if (!file)
		return (1);
	while (file)
	{
		if (file->category == INFILE || file->category == DELIMITER)
		{
			if (!open_infile(exe, file->content, builtin))
				return (0);
		}
		if (file->category == OUTFILE)
		{
			if (!open_outfile(exe, file->content, builtin))
				return (0);
		}
		if (file->category == APP_OUTFILE)
		{
			if (!open_app_outfile(exe, file->content, builtin))
				return (0);
		}
		file = file->next;
	}
	return (1);
}
