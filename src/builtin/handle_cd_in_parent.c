/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd_in_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:52:05 by poriou            #+#    #+#             */
/*   Updated: 2024/06/04 17:24:00 by poriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cd_b4_return(t_entry *entry, t_exe *exe, char *err, char *arg)
{
	ft_fprintf(2, "cd: ");
	if (arg)
		ft_fprintf(2, "%s: ", arg);
	ft_fprintf(2, "%s\n", err);
	entry->status = 1;
	free_exe(exe);
}

static void	delete_node(t_env *cur)
{
	free(cur->key);
	free(cur->value);
	free(cur);
}

static void	delete_variable(t_env *env, t_env *cur, t_env *prev)
{
	if (!env)
		return ;
	if (!prev)
		env = cur->next;
	else
		prev->next = cur->next;
	delete_node(cur);
}

static void	remove_variable(t_env *env, char *arg)
{
	t_env	*cur;
	t_env	*prev;

	if (!env || !arg || ft_strcmp(arg, "_") == 0)
		return ;
	cur = env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, arg) == 0)
			delete_variable(env, cur, prev);
		prev = cur;
		cur = cur->next;
	}
}

static bool	too_many_args(t_entry *entry, t_exe *exe, char **cmd)
{
	if (ft_str_array_len(cmd) > 2)
	{
		free_cd_b4_return(entry, exe, "too many arguments", NULL);
		return (true);
	}
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

static void	upd_env_pwd(t_env *env)
{
	char	*cwd;
	t_env	*oldpwd;
	t_env	*pwd;

	cwd = find_cwd();
	oldpwd = get_in_env(env, "OLDPWD");
	pwd = get_in_env(env, "PWD");
	if (oldpwd)
	{
		if (pwd)
		{
			free(oldpwd->value);
			oldpwd->value = pwd->value;
		}
		else
			remove_variable(env, "OLDPWD");
	}
	if (pwd)
	{
		if (!oldpwd)
			free(pwd->value);
		pwd->value = cwd;
	}
	// ft_printf("after upd_env_pwd\n");
	// ft_printf("oldpwd = %s\n", oldpwd->value);
	// ft_printf("pwd = %s\n", pwd->value);
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
	if (chdir(path) == -1)
	{
		free_cd_b4_return(entry, exe, strerror(errno), path);
		return (false);
	}
	return (true);
}

int	handle_cd_in_parent(t_entry *entry, t_exe *exe, t_env *env, char **cmd)
{
	char	*path;

	if (!cmd || exe->blocks > 1 || ft_strcmp(cmd[0], "cd") != 0)
		return (0);
	if (!get_files_fd_for_builtin(exe, exe->files, "cd"))
	{
		free_exe(exe);
		entry->status = 1;
		return (1);
	}
	if (too_many_args(entry, exe, cmd))
		return (1);
	path = get_path(entry, exe, env, cmd);
	if (!path)
		return (1);
	if (change_directory(entry, exe, path))
	{
		upd_env_pwd(env);
		ft_free_str_array(entry->env);
		entry->env = upd_env(exe, env);
		free_exe(exe);
	}
	return (1);
}
