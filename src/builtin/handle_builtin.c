/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:57:59 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/04 14:59:53 by poriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin(t_exe *exe, char *command, int prev_status)
{
	int	status;

	status = 0;
	if (ft_strcmp(command, "exit") == 0)
		status = handle_exit(exe, exe->cmd, prev_status);
	if (ft_strcmp(command, "echo") == 0)
		status = handle_echo(exe->cmd);
	if (ft_strcmp(command, "pwd") == 0)
		handle_pwd(exe);
	if (ft_strcmp(command, "cd") == 0)
		handle_cd(exe, exe->cmd);
	if (ft_strcmp(command, "env") == 0)
		status = handle_env(exe->cmd, exe->env);
	if (ft_strcmp(command, "export") == 0)
		status = handle_export(exe, exe->cmd, exe->env);
	if (ft_strcmp(command, "unset") == 0)
		status = handle_unset(exe, exe->cmd, exe->env);
	exit (status);
}
