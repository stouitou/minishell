/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:17:50 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 10:14:31 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_dup(t_exe *exe, int old_fd, int new_fd)
{
	int	ret;

	ret = dup2(old_fd, new_fd);
	if (ret == -1)
		free_subshell_and_exit(exe, strerror(errno), "dup2", EXIT_FAILURE);
}
