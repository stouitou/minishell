/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:05:01 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/29 10:21:38 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*try_path(t_exe *exe, char **path, char *cmd)
{
	int		i;
	char	*command;

	i = 0;
	while (path[i])
	{
		command = ft_strjoin(path[i], cmd);
		if (!command)
			free_subshell_and_exit(exe, ERR_MALLOC, command, 127);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

static char	*protected_strjoin(t_exe *exe, char **array, char *str)
{
	char	*join;

	join = ft_strjoin("/", str);
	if (!join)
	{
		ft_free_str_array(array);
		free_subshell_and_exit(exe, strerror(errno), "tmp in check_path", 127);
	}
	return (join);
}

char	*check_path(t_exe *exe, char *cmd)
{
	char	**path;
	char	*tmp;
	char	*command;
	char	*pathes;

	if (!exe->env)
		free_subshell_and_exit(exe, ERR_CMD, cmd, 127);
	pathes = getenv("PATH");
	if (!pathes)
		free_subshell_and_exit(exe, ERR_CMD, cmd, 127);
	path = ft_split(pathes, ":");
	if (!path)
		free_subshell_and_exit(exe, strerror(errno), "path in check_path", 127);
	tmp = protected_strjoin(exe, path, cmd);
	command = try_path(exe, path, tmp);
	if (!command)
	{
		ft_free_str_array(path);
		free(tmp);
		free_subshell_and_exit(exe, ERR_CMD, cmd, 127);
	}
	ft_free_str_array(path);
	free(tmp);
	return (command);
}
