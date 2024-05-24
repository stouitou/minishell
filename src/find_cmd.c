/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:44:00 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/24 11:33:53 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_access(t_exe *exe, char *command)
{
	struct stat	info;

	if (stat(command, &info) == -1)
	{
		init_error(exe, strerror(errno), command, 127);
		free_subshell_and_exit(exe);
	}
	// ft_printf("command = %s\n", command);
	if (S_ISDIR(info.st_mode))
	{
		// ft_printf("isdir\n");
		init_error(exe, ERR_ISDIR, command, 126);
		free_subshell_and_exit(exe);
	}
	// if (access(command, F_OK) == -1)
	// 	free_subshell_and_exit(exe, entry, strerror(errno), 127);
	if (access(command, X_OK) == -1)
	{
		init_error(exe, strerror(errno), command, 126);
		free_subshell_and_exit(exe);
	}
	return (1);
}

static char	*try_path(t_exe *exe, char **path, char *cmd)
{
	int	i;
	char	*command;

	i = 0;
	while (path[i])
	{
		command = ft_strjoin(path[i], cmd);
		if (!command)
		{
			init_error(exe, ERR_MALLOC, command, 127);
			free_subshell_and_exit(exe);
		}
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

static char	*check_path(t_exe *exe, char *cmd)
{
	char	**path;
	char	*tmp;
	char	*command;
	char	*pathes;

	if (!exe->env)
	{
		init_error(exe, ERR_CMD, cmd, 127);
		free_subshell_and_exit(exe);
	}
	pathes = getenv("PATH");
	if (!pathes)
	{
		init_error(exe, ERR_CMD, cmd, 127);
		free_subshell_and_exit(exe);
	}
	path = ft_split(pathes, ":");
	if (!path)
	{
		init_error(exe, strerror(errno), "path in check_path", 127);
		free_subshell_and_exit(exe);
	}
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
	{
		ft_free_str_array(path);
		init_error(exe, strerror(errno), "tmp in check_path", 127);
		free_subshell_and_exit(exe);
	}
	command = try_path(exe, path, tmp);
	if (!command)
	{
		ft_free_str_array(path);
		free(tmp);
		init_error(exe, ERR_CMD, cmd, 127);
		free_subshell_and_exit(exe);
	}
	ft_free_str_array(path);
	free(tmp);
	return (command);
}

static void	handle_cmd_exception(t_exe *exe, char **cmd)
{
	if (ft_strcmp(cmd[0], "..") == 0)
	{
		init_error(exe, ERR_CMD, cmd[0], 127);
		free_subshell_and_exit(exe);
	}
}

char	*find_cmd(t_exe *exe, char **cmd)
{
	char	*command;

	if (!cmd)
		return (NULL);
	if (!*cmd || !*cmd[0])
	{
		init_error(exe, ERR_CMD, NULL, 127);
		free_subshell_and_exit(exe);
	}
	handle_cmd_exception(exe, cmd);
	if (ft_strchr(cmd[0], '/') && check_access(exe, cmd[0]))
			command = cmd[0];
	else
		command = check_path(exe, cmd[0]);
	return (command);
}
