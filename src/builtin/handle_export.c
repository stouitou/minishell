/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:49:42 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 11:00:41 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_key_in_env(t_env *env, char *key)
{
	if (!key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static char	*extract_key(t_exe *exe, char *arg)
{
	char	*key;
	int		i;
	
	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
		i++;
	key = ft_strndup(arg, i);
	if (!key)
	{
		init_error(exe, ERR_MALLOC, arg, EXIT_FAILURE);
		free_subshell_and_exit(exe);
	}
	return (key);		
}

static char	*extract_value(t_exe *exe, char *arg)
{
	char	*value;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	value = ft_strdup(arg + i + 1);
	if (!value)
	{
		init_error(exe, ERR_MALLOC, arg, EXIT_FAILURE);
		free_subshell_and_exit(exe);
	}
	return (value);
}

static void	upd_concatenating(t_exe *exe, t_env *env, char *key, char *value)
{
	t_env	*relevant;
	char	*new;

	relevant = find_key_in_env(env, key);
	new = ft_strjoin(relevant->value, value);
	if (!new)
	{
		init_error(exe, ERR_MALLOC, value, EXIT_FAILURE);
		free_subshell_and_exit(exe);
	}
	free(relevant->value);
	relevant->value = new;
}

static void	upd_replacing(t_exe *exe, t_env *env, char *key, char *value)
{
	t_env	*relevant;
	char	*new;

	relevant = find_key_in_env(env, key);
	new = ft_strdup(value);
	if (!new)
	{
		init_error(exe, ERR_MALLOC, value, EXIT_FAILURE);
		free_subshell_and_exit(exe);
	}
	free(relevant->value);
	relevant->value = new;
}

static bool	addition_operator(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i - 1] == '+')
		return (true);
	return (false);
}

static bool	exists_in_env(t_exe *exe, char *key)
{
	t_env	*cur;

	cur = exe->env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (true);
		cur = cur->next;
	}
	return (false);
}

static bool	syntax_error(char *arg, int *exit_status)
{
	int		i;

	if (!arg)
		return (true);
	i = 0;
	if (!arg[i] || arg[i] == '=' || arg[i] == '\0' || ft_isdigit(arg[i]))
	{
		ft_printf("export: '%s': not a valid identifier\n", arg);
		*exit_status = 1;
		return (true);
	}
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_printf("export: '%s': not a valid identifier\n", arg);
			*exit_status = 1;
			return (true);
		}
		i++;
	}
	if (!arg[i])
		return (true);
	if ((arg[i] == '+' && arg[i + 1] != '='))
	{
		ft_printf("export: '%s': not a valid identifier\n", arg);
		*exit_status = 1;
		return (true);
	}
	return (false);
}

void	handle_export(t_exe *exe, char **cmd, t_env *env)
{
	int		exit_status;
	char	*key;
	char	*value;
	t_env	*new;
	int		i;
	
	if (!env)
		exit (1) ;
	if (!get_files_fd_for_exit(exe, exe->files))
	{
		free_exe(exe);
		exit (1);
	}
	exit_status = 0;
	i = 1;
	if (!cmd[i])
		export_only(exe, env);
	while (cmd[i])
	{
		if (syntax_error(cmd[i], &exit_status))
		{
			i++;
			continue ;
		}
		key = extract_key(exe, cmd[i]);
		value = extract_value(exe, cmd[i]);
		if (exists_in_env(exe, key))
		{
			if (addition_operator(cmd[i]))
				upd_concatenating(exe, env, key, value);
			else
				upd_replacing(exe, env, key, value);
			i++;
			continue ;
		}
		new = env_new(key, value);
		if (!new)
		{
			init_error(exe, ERR_MALLOC, value, EXIT_FAILURE);
			free_subshell_and_exit(exe);
		}
		env_addback(&env, new);
	}
	exit (exit_status);
}
