/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:37:18 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/22 15:47:11 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_files_fd_for_exit(t_exe *exe, t_files *file)
{
	if (!file)
		return (1);
	while (file)
	{
		if (file->category == INFILE)
		{
			if (exe->io_fd[0] != -1)
				close (exe->io_fd[0]);
			if (access(file->content, F_OK | R_OK) == -1)
			{
				ft_fprintf(2, "%s: %s\n", file->content, strerror(errno));
				init_error(exe, strerror(errno), file->content, EXIT_FAILURE);
				return (0);
			}
			exe->io_fd[0] = open(file->content, O_RDONLY);
			if (exe->io_fd[0] == -1)
			{
				ft_fprintf(2, "%s: %s\n", file->content, strerror(errno));
				init_error(exe, strerror(errno), file->content, EXIT_FAILURE);
				return (0);
			}
		}
		if (file->category == OUTFILE)
		{
			if (exe->io_fd[1] != -1)
				close (exe->io_fd[1]);
			if (access(file->content, F_OK) == 0)
			{
				if (access(file->content, W_OK) == -1)
				{
					ft_fprintf(2, "%s: %s\n", file->content, strerror(errno));
					init_error(exe, strerror(errno), file->content, EXIT_FAILURE);
					return (0);
				}
			}
			exe->io_fd[1] = open(file->content, O_CREAT | O_WRONLY | O_TRUNC, 00666);
			if (exe->io_fd[1] == -1)
			{
				ft_fprintf(2, "%s: %s\n", file->content, strerror(errno));
				init_error(exe, strerror(errno), file->content, EXIT_FAILURE);
				return (0);
			}
		}
		if (file->category == APP_OUTFILE)
		{
			if (exe->io_fd[1] != -1)
				close (exe->io_fd[1]);
			if (access(file->content, F_OK) == 0)
			{
				if (access(file->content, W_OK) == -1)
				{
					ft_fprintf(2, "%s: %s\n", file->content, strerror(errno));
					init_error(exe, strerror(errno), file->content, EXIT_FAILURE);
					return (0);
				}
			}
			exe->io_fd[1] = open(file->content, O_CREAT | O_WRONLY | O_APPEND, 00666);
			if (exe->io_fd[1] == -1)
			{
				ft_fprintf(2, "%s: %s\n", file->content, strerror(errno));
				init_error(exe, strerror(errno), file->content, EXIT_FAILURE);
				return (0);
			}
		}
		file = file->next;
	}
	return (1);
}
