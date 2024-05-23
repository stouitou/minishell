/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:25:04 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/23 12:12:26 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtin(t_entry *entry, t_exe *exe, char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		handle_exit(entry, exe, exe->cmd);
	if (ft_strcmp(command, "export") == 0)
		handle_export(entry, exe, exe->cmd, exe->env);
}
