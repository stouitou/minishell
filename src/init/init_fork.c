/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:58:56 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/13 13:36:35 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	init_fork(t_exe *exe, t_token **token)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		if (exe->pipe_fd1[0] != -1)
			close(exe->pipe_fd1[0]);
		if (exe->pipe_fd1[1] != -1)
			close(exe->pipe_fd1[1]);
		if (exe->pipe_fd2[0] != -1)
			close(exe->pipe_fd2[0]);
		if (exe->pipe_fd2[1] != -1)
			close(exe->pipe_fd2[1]);
		free_exe(exe);
		free_token_and_exit(token, strerror(errno), NULL, EXIT_FAILURE);
	}
	return (pid);
}
