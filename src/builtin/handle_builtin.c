/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:25:04 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/23 11:30:09 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin(t_entry *entry, t_exe *exe, char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		handle_exit(entry, exe, exe->cmd);
	if (ft_strcmp(command, "env") == 0)
		handle_env(exe->cmd, exe->env);
	exit (0);
}
