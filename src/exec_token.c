/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:05:58 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/14 11:42:53 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	/* VOIR DANS ALL TESTS LOGS :
		< infile cat > ok > infile2
		| < infile cat >> ok > infile2
	*/

void	exec_token(t_entry *entry, t_token *token, char **env)
{
	t_exe	exe;
	// int		blocks;
	int		i;
	int		status;
	// t_error	error;

	if (!entry->token)
		return ;
	exe.blocks = token->head->block + 1;
	exe.pipe_fd1[0] = -1;
	exe.pipe_fd1[1] = -1;
	exe.pipe_fd2[0] = -1;
	exe.pipe_fd2[1] = -1;
	// exe.error = error;
	i = 0;
	while (i < exe.blocks)
	{
		// ft_printf("i = %d\n", i);
		init_exe(entry, &exe, env, i);
		if (i < (exe.blocks - 1) && (i % 2 == 0))
			init_pipe(&token, &exe, exe.pipe_fd1);
		if (i < (exe.blocks - 1) && (i % 2 != 0))
			init_pipe(&token, &exe, exe.pipe_fd2);
		exe.subshell = init_fork(&exe, &token);
		if (exe.subshell == 0)
			exec_subshell(entry, &exe, i);
		// if (ft_strcmp(exe.error.msg, ERR_MALLOC) == 0)
		// {
		// 	close_both_fd(exe.pipe_fd1[0], exe.pipe_fd1[1]);
		// 	close_both_fd(exe.pipe_fd2[0], exe.pipe_fd2[1]);
		// 	free_exe(&exe);
		// 	token_clear(&token);
		// 	exit (EXIT_FAILURE);
		// }
		free_exe(&exe);
		if (i % 2 != 0)
		{
			close_both_fd(exe.pipe_fd1[0], exe.pipe_fd1[1]);
			exe.pipe_fd1[0] = -1;
			exe.pipe_fd1[1] = -1;
		}
		if (i && (i % 2 == 0))
		{
			close_both_fd(exe.pipe_fd2[0], exe.pipe_fd2[1]);
			exe.pipe_fd2[0] = -1;
			exe.pipe_fd2[1] = -1;
		}
		i++;
	}
	close_all_fd(&exe);
	while (errno != ECHILD)
	{
		if (wait(&status) == exe.subshell && exe.blocks == i)
			entry->status = WEXITSTATUS(status);
		// wait(&status);
		// entry->status = WEXITSTATUS(status);
	}
}
