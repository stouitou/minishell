/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd_in_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:52:05 by poriou            #+#    #+#             */
/*   Updated: 2024/06/06 10:08:52 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	too_many_args(t_entry *entry, t_exe *exe, char **cmd)
{
	if (ft_str_array_len(cmd) > 2)
	{
		free_cd_b4_return(entry, exe, "too many arguments", NULL);
		return (true);
	}
	return (false);
}

static char	*handle_hyphen(t_entry *entry, t_exe *exe, t_env *env)
{
	t_env	*oldpwd;

	oldpwd = get_in_env(env, "OLDPWD");
	if (!oldpwd)
	{
		free_cd_b4_return(entry, exe, "OLDPWD not set", NULL);
		entry->status = 1;
		return (NULL);
	}
	return (oldpwd->value);
}

static char	*get_path(t_entry *entry, t_exe *exe, t_env *env, char **cmd)
{
	char	*path;

	path = NULL;
	if (ft_str_array_len(cmd) == 1)
	{
		path = extract_key_value(env, "HOME");
		if (!path)
		{
			free_cd_b4_return(entry, exe, "HOME not set", NULL);
			entry->status = 1;
			return (NULL);
		}
	}
	else
		path = cmd[1];
	if (ft_strcmp(path, "-") == 0)
	{
		path = handle_hyphen(entry, exe, env);
		if (!path)
			return (NULL);
	}
	return (path);
}

static bool	change_directory(t_entry *entry, t_exe *exe, char *path)
{
	int		res;
	char	*cwd;

	res = chdir(path);
	if (res == -1)
	{
		free_cd_b4_return(entry, exe, strerror(errno), path);
		return (false);
	}
	cwd = find_cwd();
	if (!cwd)
	{
		ft_fprintf(2, "cd: error retrieving current directory: ");
		ft_fprintf(2, "getcwd: cannot access parent directories: ");
		ft_fprintf(2, "%s\n", strerror(errno));
		entry->status = 1;
	}
	return (true);
}

bool	handle_cd_in_parent(t_entry *entry, t_exe *exe, t_env *env, char **cmd)
{
	char	*path;

	if (!get_files_fd_for_builtin(exe, exe->files, "cd"))
	{
		free_exe(exe);
		entry->status = 1;
		return (true);
	}
	if (too_many_args(entry, exe, cmd))
		return (true);
	path = get_path(entry, exe, env, cmd);
	if (!path)
		return (true);
	if (change_directory(entry, exe, path))
	{
		upd_env_pwd(env);
		ft_free_str_array(entry->env);
		entry->env = upd_env(exe, env);
		free_exe(exe);
	}
	return (true);
}
