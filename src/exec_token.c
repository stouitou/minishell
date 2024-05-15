/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:05:58 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/15 17:09:37 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pipe_fd_and_block(t_entry *entry, t_exe *exe)
{
	exe->pipe_fd1[0] = -1;
	exe->pipe_fd1[1] = -1;
	exe->pipe_fd2[0] = -1;
	exe->pipe_fd2[1] = -1;
	exe->blocks = entry->token->head->block + 1;
}

static void close_pipe_fd_if_needed(t_exe *exe, int i)
{
	if (i % 2 != 0)
	{
		close_both_fd(exe->pipe_fd1[0], exe->pipe_fd1[1]);
		exe->pipe_fd1[0] = -1;
		exe->pipe_fd1[1] = -1;
	}
	if (i && (i % 2 == 0))
	{
		close_both_fd(exe->pipe_fd2[0], exe->pipe_fd2[1]);
		exe->pipe_fd2[0] = -1;
		exe->pipe_fd2[1] = -1;
	}
}

void	exec_token(t_entry *entry, t_token *token, char **env)
{
	t_exe	exe;
	int		i;
	int		status;

	if (!entry->token)
		return ;
	init_pipe_fd_and_block(entry, &exe);
	i = 0;
	while (i < exe.blocks)
	{
		init_exe(entry, &exe, env, i);
		if (i < (exe.blocks - 1) && (i % 2 == 0))
			init_pipe(&token, &exe, exe.pipe_fd1);
		if (i < (exe.blocks - 1) && (i % 2 != 0))
			init_pipe(&token, &exe, exe.pipe_fd2);
		exe.subshell = init_fork(&exe, &token);
		if (exe.subshell == 0)
			exec_subshell(&exe, i);
		free_exe(&exe);
		close_pipe_fd_if_needed(&exe, i);
		i++;
	}
	close_all_fd(&exe);
	while (errno != ECHILD)
	{
		if (wait(&status) == exe.subshell && exe.blocks == i)
			entry->status = WEXITSTATUS(status);
	}
}
