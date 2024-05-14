/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:38:19 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/13 13:41:51 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fd(t_exe *exe)
{
	int	i;

	if (!exe)
		return ;
	if (exe->pipe_fd1[0] != -1)
		close(exe->pipe_fd1[0]);
	if (exe->pipe_fd1[1] != -1)
		close(exe->pipe_fd1[1]);
	if (exe->pipe_fd2[0] != -1)
		close(exe->pipe_fd2[0]);
	if (exe->pipe_fd2[1] != -1)
		close(exe->pipe_fd2[1]);
	i = 0;
	while (i < 4)
	{
		if (exe->ioda_fd[i] != -1)
			close(exe->ioda_fd[i]);
		i++;
	}
}
