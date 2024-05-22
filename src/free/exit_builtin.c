/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:24:37 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/21 15:17:25 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_builtin(t_exe *exe, char *builtin)
{
	close_all_fd(exe);
	if (builtin)
		ft_fprintf(2, "%s: ", builtin);
	if (exe->error.data)
		ft_fprintf(2, "%s: ", exe->error.data);
	if (exe->error.msg)
		ft_fprintf(2, "%s", exe->error.msg);
	if (exe->error.msg)
		ft_fprintf(2, "\n");
	exit(exe->error.status);
}
