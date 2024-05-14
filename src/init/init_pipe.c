/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:48:21 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/13 13:38:01 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(t_token **token, t_exe *exe, int *pipe_fd)
{
	int ret;

	ret = pipe(pipe_fd);
	// printf("is piped\n");
	if (ret == -1)
	{
		free_exe(exe);
		free_token_and_exit(token, strerror(errno), NULL, EXIT_FAILURE);
	}
}
