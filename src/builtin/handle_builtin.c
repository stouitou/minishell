/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:57:59 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/23 12:58:00 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin(t_entry *entry, t_exe *exe, char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		handle_exit(entry, exe, exe->cmd);
	if (ft_strcmp(command, "export") == 0)
		handle_export(entry, exe, exe->cmd, exe->env);
	if (ft_strcmp(command, "env") == 0)
		handle_env(exe->cmd, exe->env);
	if (ft_strcmp(command, "echo") == 0)
		handle_echo(exe, exe->cmd);
	exit (0);

}
