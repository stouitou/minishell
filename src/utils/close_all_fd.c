/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:38:19 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 16:34:36 by stouitou         ###   ########.fr       */
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
	while (i < 3)
	{
		if (exe->iod_fd[i] != -1)
		{
			// ft_printf("closing exe->iod_fd[%d]", exe->iod_fd[i]);
			close(exe->iod_fd[i]);
		}
		i++;
	}
}
