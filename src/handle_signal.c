/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:46:01 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/12 17:10:25 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sgl)
{
	if (sgl == SIGINT)
	{
		g_sig = 130;
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal_in_subshell(int sgl)
{
	if (sgl == SIGINT)
	{
		g_sig = 130;
		exit (130);
	}
}

void	handle_signal_in_heredoc(int sgn)
{
	int		pipefd[2];
	pid_t	pid;

	if (sgn == SIGINT)
	{
		pipe(pipefd);
		write(1, "\n", 1);
		pid = fork();
		if (pid == 0)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			write(pipefd[1], "\n", 1);
			close_both_fd(pipefd[1], pipefd[0]);
			exit(0);
		}
		else
		{
			dup2(pipefd[0], STDIN_FILENO);
			close_both_fd(pipefd[0], pipefd[1]);
			wait(&pid);
		}
		g_sig = 130;
	}
}
