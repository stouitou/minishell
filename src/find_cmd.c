/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:44:00 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/30 09:17:32 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cmd_exception(t_exe *exe, char **cmd)
{
	if (ft_strcmp(cmd[0], "..") == 0)
		free_subshell_and_exit(exe, ERR_CMD, cmd[0], 127);
}

static int	check_access(t_exe *exe, char *command)
{
	struct stat	info;

	if (stat(command, &info) == -1)
		free_subshell_and_exit(exe, strerror(errno), command, 127);
	if (S_ISDIR(info.st_mode))
		free_subshell_and_exit(exe, ERR_ISDIR, command, 126);
	if (access(command, X_OK) == -1)
		free_subshell_and_exit(exe, strerror(errno), command, 126);
	return (1);
}

char	*find_cmd(t_exe *exe, char **cmd)
{
	char	*command;

	if (!cmd)
		return (NULL);
	if (!*cmd || !*cmd[0])
		free_subshell_and_exit(exe, ERR_CMD, NULL, 127);
	handle_cmd_exception(exe, cmd);
	// ft_printf("HERE\n");
	if (ft_strchr(cmd[0], '/') && check_access(exe, cmd[0]))
	{
		// ft_printf("HERE 1\n");
		command = cmd[0];
	}
	else
	{
		// ft_printf("HERE 2\n");
		command = check_path(exe, cmd[0]);
	}
	return (command);
}
