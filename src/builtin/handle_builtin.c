/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:57:59 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/24 16:41:00 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin(t_entry *entry, t_exe *exe, char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		handle_exit(exe, exe->cmd);
	if (ft_strcmp(command, "echo") == 0)
		handle_echo(exe, exe->cmd);
	if (ft_strcmp(command, "env") == 0)
		handle_env(exe->cmd, exe->env);
	if (ft_strcmp(command, "export") == 0)
		handle_export(exe, exe->cmd, exe->env);
	free(entry->env);
	entry->env = upd_env(exe, exe->env);
	// print_tab(entry->env);
	exit (0);

}
