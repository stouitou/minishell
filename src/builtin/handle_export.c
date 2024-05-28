/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:49:42 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 16:07:30 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_export(t_exe *exe, char **cmd, t_env *env)
{
	int		exit_status;
	int		i;

	if (!env)
		return (1);
	if (!get_files_fd_for_builtin(exe, exe->files, "export"))
	{
		free_exe(exe);
		return (1);
	}
	exit_status = 0;
	i = 1;
	if (!cmd[i])
		export_only(exe, env);
	while (cmd[i])
	{
		export_variable(exe, env, cmd[i], &exit_status);
		i++;
	}
	return (exit_status);
}
