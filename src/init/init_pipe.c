/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:48:21 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 11:33:41 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(t_entry *entry, t_exe *exe, int *pipe_fd)
{
	int	ret;

	ret = pipe(pipe_fd);
	if (ret == -1)
	{
		free_exe(exe);
		free_token_and_exit(entry, strerror(errno), NULL, EXIT_FAILURE);
	}
}
