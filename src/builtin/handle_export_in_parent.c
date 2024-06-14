/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export_in_parent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:52:11 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/12 14:12:55 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_export_in_parent(t_entry *ent, t_exe *ex, t_env *env, char **cmd)
{
	int		exit_status;
	int		i;

	if (!get_files_fd_for_builtin(ex, ex->files, "export"))
	{
		free_exe(ex);
		ent->status = 1;
		return (true);
	}
	exit_status = 0;
	i = 1;
	if (!cmd[i])
		export_only(ex, env);
	while (cmd[i])
	{
		export_variable(ex, &env, cmd[i], &exit_status);
		i++;
	}
	ent->status = exit_status;
	ft_free_str_array(ent->env);
	ent->env = upd_env(ex, env);
	free_exe(ex);
	return (true);
}
