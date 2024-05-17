/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:17:50 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/17 16:34:42 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_dup(t_exe *exe, int old_fd, int new_fd)
{
	int	ret;

	// dprintf(2, "1 dupped, %d %d\n", old_fd, new_fd);
	ret = dup2(old_fd, new_fd);
	if (ret == -1)
	{
		init_error(exe, strerror(errno), "dup2", EXIT_FAILURE);
		free_subshell_and_exit(exe);
	}
	// dprintf(2, "2 dupped, %d %d\n", old_fd, new_fd);
}
