/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export_in_parent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:52:11 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 11:54:19 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_export_in_parent(t_entry *entry, t_exe *exe, t_env *env, char **cmd)
{
	int		exit_status;
	int		i;

	if (!cmd || exe->blocks > 1 || ft_strcmp(cmd[0], "export") != 0)
		return (0);
	if (!get_files_fd_for_builtin(exe, exe->files, "export"))
	{
		free_exe(exe);
		entry->status = 1;
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
	entry->status = exit_status;
	ft_free_str_array(entry->env);
	entry->env = upd_env(exe, env);
	free_exe(exe);
	return (1);
}
