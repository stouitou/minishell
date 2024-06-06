/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:52:05 by poriou            #+#    #+#             */
/*   Updated: 2024/06/05 17:38:03 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	too_many_args(t_exe *exe, char **cmd)
{
	if (ft_str_array_len(cmd) > 2)
		free_subshell_and_exit(exe, "too many arguments", "cd", 1);
	return (false);
}

static char	*extract_key_value(t_env *env, char *key)
{
	t_env	*cur;
	char	*value;

	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			value = cur->value;
			return (value);
		}
		cur = cur->next;
	}
	return (NULL);
}

static t_env	*get_in_env(t_env *env, char *key)
{
	t_env	*result;

	if (!env)
		return (NULL);
	result = env;
	while (result)
	{
		if (ft_strcmp(result->key, key) == 0)
			return (result);
		result = result->next;
	}
	return (NULL);
}

static char	*find_cwd(void)
{
	char	*pwd;
	char	*buf;
	int		size;

	buf = NULL;
	size = 0;
	while (1)
	{
		pwd = getcwd(buf, size);
		if (!pwd && errno == ERANGE)
		{
			size++;
			continue ;
		}
		else if (!pwd)
			return (NULL);
		break ;
	}
	return (pwd);
}

static char	*handle_hyphen(t_exe *exe, t_env *env)
{
	t_env	*oldpwd;

	oldpwd = get_in_env(env, "OLDPWD");
	if (!oldpwd)
		free_subshell_and_exit(exe, "OLDPWD not set", "cd", 1);
	return (oldpwd->value);
}

static char	*get_path(t_exe *exe, t_env *env, char **cmd)
{
	char	*path;

	path = NULL;
	if (ft_str_array_len(cmd) == 1)
	{
		path = extract_key_value(env, "HOME");
		if (!path)
			free_subshell_and_exit(exe, "HOME not set", "cd", 1);
	}
	else
		path = cmd[1];
	if (ft_strcmp(path, "-") == 0)
	{
		path = handle_hyphen(exe, env);
		if (!path)
			return (NULL);
	}
	return (path);
}

static bool	change_directory(t_exe *exe, char *path)
{
	int		res;
	char	*cwd;

	res = chdir(path);
	if (res == -1)
	{
		ft_fprintf(2, "cd: ");
		free_subshell_and_exit(exe, strerror(errno), path, 1);
	}
	cwd = find_cwd();
	if (!cwd)
	{
		ft_fprintf(2, "cd: error retrieving current directory: ");
		ft_fprintf(2, "getcwd: cannot access parent directories: ");
		ft_fprintf(2, "%s\n", strerror(errno));
		free_subshell_and_exit(exe, NULL, NULL, 1);
	}
	return (true);
}

int	handle_cd(t_exe *exe, t_env *env, char **cmd)
{
	char	*path;

	if (!env)
		return (1);
	if (!get_files_fd_for_builtin(exe, exe->files, "cd"))
	{
		free_exe(exe);
		return (1);
	}
	if (too_many_args(exe, cmd))
		return (1);
	path = get_path(exe, env, cmd);
	if (!path)
		return (1);
	if (change_directory(exe, path))
		return (0);
	return (1);
}
