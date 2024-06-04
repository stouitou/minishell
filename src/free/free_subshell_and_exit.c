/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_subshell_and_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:24:37 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 10:08:30 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_subshell_and_exit(t_exe *exe, char *msg, char *data, int status)
{
	init_error(exe, msg, data, status);
	close_all_fd(exe);
	if (exe->error.data)
		ft_fprintf(2, "%s: ", exe->error.data);
	if (exe->error.msg)
		ft_fprintf(2, "%s", exe->error.msg);
	if (exe->error.msg)
		ft_fprintf(2, "\n");
	exit(exe->error.status);
}
