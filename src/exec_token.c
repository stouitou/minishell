/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:05:58 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/06 16:33:07 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	protected_unlink(t_entry *entry, char *file)
{
	int	ret;

	ret = unlink(file);
	if (ret == -1)
		free_token_and_exit(entry, strerror(errno), file, EXIT_FAILURE);
}

static void	close_pipe_fd_if_needed(t_exe *exe, int i)
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

static void	pipe_fork_exec_reset(t_entry *entry, t_exe *exe, int *i)
{
	if (*i < (exe->blocks - 1) && (*i % 2 == 0))
		init_pipe(entry, exe, exe->pipe_fd1);
	if (*i < (exe->blocks - 1) && (*i % 2 != 0))
		init_pipe(entry, exe, exe->pipe_fd2);
	exe->subshell = init_fork(exe, entry);
	if (exe->subshell == 0)
		exec_subshell(exe, *i, entry->prev_status);
	free(entry->env);
	entry->env = upd_env(exe, exe->env);
	free_exe(exe);
	close_pipe_fd_if_needed(exe, *i);
	(*i)++;
}

static void	wait_for_child(t_entry *entry, t_exe exe, int status, int i)
{
	while (errno != ECHILD)
	{
		if (wait(&status) == exe.subshell && exe.blocks == i)
		{
			// ft_printf("here\n");
			entry->status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
            if (WTERMSIG(status) == SIGINT)
			{
				entry->status = WTERMSIG(status);
                // printf("Terminé par SIGINT\n");
            } 
			else if (WTERMSIG(status) == SIGQUIT)
			{
				entry->status = WTERMSIG(status);
                // printf("Terminé par SIGQUIT\n");
            }
        }
	}
}

void	exec_token(t_entry *entry, t_token *token)
{
	t_exe	exe;
	int		i;
	int		status;

	if (!token)
		return ;
	init_pipe_fd_and_block(entry, &exe);
	i = 0;
	status = 0;
	// ft_printf("sgl in exec token = %d\n", sgl);
	while (i < exe.blocks)
	{
		init_exe(entry, token, &exe, i);
		if (handle_builtin_in_parent(entry, &exe, exe.env, exe.cmd))
			break ;
		else
			pipe_fork_exec_reset(entry, &exe, &i);
	}
	close_all_fd(&exe);
	// if (exe.blocks > 0)
	wait_for_child(entry, exe, status, i);
	// listen_signals();
	if (entry->heredoc)
		protected_unlink(entry, H_FILE);
}

		// if (handle_exit_in_parent(entry, &exe, exe.cmd)
		// 	|| handle_export_in_parent(entry, &exe, exe.env, exe.cmd)
		// 	|| handle_cd_in_parent(entry, &exe, exe.env, exe.cmd)
		// 	|| handle_unset_in_parent(entry, &exe, exe.env, exe.cmd))
		// 	break ;
