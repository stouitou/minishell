/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd_in_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:52:05 by poriou            #+#    #+#             */
/*   Updated: 2024/05/28 14:13:18 by poriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cd_b4_return(t_entry *entry, t_exe *exe, char *err, int status)
{
	free_exe(exe);
	ft_fprintf(2, err);
	entry->status = status;
}

static bool	key_exists_in_env(char *key, t_env *env)
{
	if (!env)
		return (false);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (true);
		env = env->next;
	}
	return (false);
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

static void	upd_pwd_env(t_entry *entry, t_exe *exe, t_env *env, char *path)
{
	t_env	*pwd;
	t_env	*oldpwd;
	bool	pwd_exists;
	bool	oldpwd_exists;

	// if (!key_exists_in_env("PWD", env))
	// {
	// 	oldpwd = get_in_env("OLDPWD", env);
	// 	if (!oldpwd)
	// 		return ;
	// 	free(oldpwd->value);
	// 	oldpwd->value = ft_strdup("");
	// 	if (!oldpwd->value && errno == ENOMEM)
	// 		free_token_and_exit(entry, strerror(errno), path, EXIT_FAILURE);
	// }
	pwd = get_in_env("PWD", env);
	if (!pwd)
		pwd_exists = false;
	else
		pwd_exists = true;
	oldpwd = get_in_env("OLDPWD", env);
	if (!oldpwd)
		oldpwd_exists = false;
	else
		oldpwd_exists = true;
	if (oldpwd_exists && pwd_exists)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(pwd->value);
		if (!pwd->value && errno == ENOMEM)
			free_token_and_exit(entry, strerror(errno), path, EXIT_FAILURE);
	}
	if (oldpwd_exists && !pwd_exists)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup("");
		if (!oldpwd->value && errno == ENOMEM)
			free_token_and_exit(entry, strerror(errno), path, EXIT_FAILURE);
	}
	if (pwd_exists)
	{
		free(pwd->value);
		pwd->value = ft_strdup(path);
		if (!pwd->value && errno == ENOMEM)
			free_token_and_exit(entry, strerror(errno), path, EXIT_FAILURE);
	}
	// if (key_exists_in_env("OLDPWD", env))
	// {
	// 	oldpwd = get_in_env("OLDPWD", env);
	// 	pwd = get_in_env("PWD", env);
	// 	free(oldpwd->value);
	// 	oldpwd->value = ft_strdup(path);
	// 	if (!pwd->value)
	// 		free_token_and_exit(entry, strerror(errno), path, EXIT_FAILURE);
	// }
	// if (key_exists_in_env("PWD", env))
	// {
	// 	pwd = find_key_in_env("PWD", env);
	// 	free(pwd->value);
	// 	pwd->value = ft_strdup(path);
	// 	if (!pwd->value)
	// 		free_token_and_exit(entry, strerror(errno), path, EXIT_FAILURE);
	// }
}

static bool	too_many_args(t_entry *entry, t_exe *exe, char **cmd)
{
	if (ft_str_array_len(cmd) > 2)
	{
		free_cd_b4_return(entry, exe, "cd: too many arguments\n", 1);
		return (true);
	}
	return (false);
}

int	handle_cd_in_parent(t_entry *entry, t_exe *exe, t_env *env, char **cmd)
{
	t_env	*oldpwd;
	t_env	*pwd;
	int		exit_status;
	int		size;
	char	*old_path;
	char	*path;

	(void)env;
	if (!cmd || exe->blocks > 1 || ft_strcmp(cmd[0], "cd") != 0)
		return (0);
	if (!get_files_fd_for_exit(exe, exe->files))
	{
		free_exe(exe);
		entry->status = 1;
		return (1);
	}
	if (too_many_args(entry, exe, cmd))
		return (1);
	oldpwd = get_in_env(env, "OLDPWD");
	pwd = get_in_env(env, "PWD");
	upd_oldpwd(entry, env, oldpwd, pwd);
	entry->status = exit_status;
	return (1);
}

// int	handle_cd_in_parent(t_entry *entry, t_exe *exe, t_env *env, char **cmd)
// {
// 	int		exit_status;
// 	int		size;
// 	char	*old_path;
// 	char	*path;

// 	(void)env;
// 	if (!cmd || exe->blocks > 1 || ft_strcmp(cmd[0], "cd") != 0)
// 		return (0);
// 	if (!get_files_fd_for_exit(exe, exe->files))
// 	{
// 		free_exe(exe);
// 		entry->status = 1;
// 		return (1);
// 	}
// 	if (ft_str_array_len(cmd) > 2)
// 	{
// 		free_cd_b4_return(entry, exe, "cd: too many arguments\n", 1);
// 		return (1);
// 	}
// 	exit_status = 0;
// 	size = 0;
// 	old_path = getenv("PWD");
// 	path = NULL;
// 	if (!cmd[1])
// 	{
// 		path = getenv("HOME");
// 		if (!path)
// 		{
// 			free_cd_b4_return(entry, exe, "cd: HOME not set\n", 1);
// 			return (1);
// 		}
// 		if (chdir(path) == -1)
// 			perror("chdir");
// 		upd_pwd_env(entry, exe, env, path);
// 		entry->status = exit_status;
// 		return (1);
// 	}
// 	if (ft_strcmp(cmd[1], "-") == 0)
// 	{
// 		path = getenv("OLDPWD");
// 		if (!path)
// 		{
// 			free_cd_b4_return(entry, exe, "cd: OLDPWD not set\n", 1);
// 			return (1);
// 		}
// 		if (chdir(path) == -1)
// 			perror("chdir");
// 		entry->status = exit_status;
// 		return (1);
// 	}
// 	entry->status = exit_status;
// 	return (1);
// }
