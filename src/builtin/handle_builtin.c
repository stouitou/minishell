/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:57:59 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 10:40:03 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin(t_exe *exe, char *command, int prev_status)
{
	if (ft_strcmp(command, "exit") == 0)
		handle_exit(exe, exe->cmd, prev_status);
	if (ft_strcmp(command, "echo") == 0)
		handle_echo(exe, exe->cmd);
	if (ft_strcmp(command, "env") == 0)
		handle_env(exe->cmd, exe->env);
	if (ft_strcmp(command, "export") == 0)
		handle_export(exe, exe->cmd, exe->env);
	if (ft_strcmp(command, "unset") == 0)
		handle_unset(exe, exe->cmd, exe->env);
	exit (0);

}
