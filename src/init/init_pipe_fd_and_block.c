/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe_fd_and_block.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:44:13 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 09:44:36 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe_fd_and_block(t_entry *entry, t_exe *exe)
{
	exe->pipe_fd1[0] = -1;
	exe->pipe_fd1[1] = -1;
	exe->pipe_fd2[0] = -1;
	exe->pipe_fd2[1] = -1;
	exe->blocks = entry->token->head->block + 1;
}
