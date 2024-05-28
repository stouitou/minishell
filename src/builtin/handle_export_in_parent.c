/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export_in_parent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:52:11 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 12:31:23 by stouitou         ###   ########.fr       */
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

static char	*extract_key(t_entry *entry, char *arg)
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
		free_token_and_exit(entry, strerror(errno), arg, EXIT_FAILURE);
	return (key);
}

static char	*extract_value(t_entry *entry, char *arg)
{
	char	*value;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	value = ft_strdup(arg + i + 1);
	if (!value)
		free_token_and_exit(entry, strerror(errno), arg, EXIT_FAILURE);
	return (value);
}

static void	upd_concatenating(t_entry *entry, t_env *env, char *key, char *value)
{
	t_env	*relevant;
	char	*new;

	relevant = find_key_in_env(env, key);
	new = ft_strjoin(relevant->value, value);
	if (!new)
		free_token_and_exit(entry, strerror(errno), key, EXIT_FAILURE);
	free(relevant->value);
	relevant->value = new;
}

static void	upd_replacing(t_entry *entry, t_env *env, char *key, char *value)
{
	t_env	*relevant;
	char	*new;

	relevant = find_key_in_env(env, key);
	new = ft_strdup(value);
	if (!new)
		free_token_and_exit(entry, strerror(errno), key, EXIT_FAILURE);
	free(relevant->value);
	relevant->value = new;
}

// static void	change_value(t_entry *entry, t_env *cur, char *arg, char *value)
// {
// 	int		i;
// 	char	*new;

// 	i = 0;
// 	while (arg[i] && arg[i] != '=')
// 		i++;
// 	if (arg[i - 1] == '+')
// 	{
// 		new = ft_strjoin(cur->value, value);
// 		if (!new)
// 			free_token_and_exit(entry, strerror(errno), arg, EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		new = ft_strdup(value);
// 		if (!new)
// 			free_token_and_exit(entry, strerror(errno), arg, EXIT_FAILURE);
// 	}
// 	free(cur->value);
// 	cur->value = new;
// }

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
		ft_fprintf(2, "export: '%s': not a valid identifier\n", arg);
		*exit_status = 1;
		return (true);
	}
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_fprintf(2, "export: '%s': not a valid identifier\n", arg);
			*exit_status = 1;
			return (true);
		}
		i++;
	}
	if (!arg[i])
		return (true);
	if ((arg[i] == '+' && arg[i + 1] != '='))
	{
		ft_fprintf(2, "export: '%s': not a valid identifier\n", arg);
		*exit_status = 1;
		return (true);
	}
	return (false);
}

int	handle_export_in_parent(t_entry *entry, t_exe *exe, t_env *env, char **cmd)
{
	int		exit_status;
	char	*key;
	char	*value;
	t_env	*new;
	int		i;

	if (!cmd || exe->blocks > 1 || ft_strcmp(cmd[0], "export") != 0)
		return (0);
	if (!get_files_fd_for_builtin(exe, exe->files))
	{
		free_exe(exe);
		entry->status = 1;
		return (1);
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
		key = extract_key(entry, cmd[i]);
		value = extract_value(entry, cmd[i]);
		if (exists_in_env(exe, key))
		{
			if (addition_operator(cmd[i]))
				upd_concatenating(entry, env, key, value);
			else
				upd_replacing(entry, env, key, value);
			i++;
			continue ;
		}
		new = env_new(key, value);
		if (!new)
			free_token_and_exit(entry, ERR_MALLOC, value, EXIT_FAILURE);
		env_addback(&env, new);
		i++;
	}
	entry->status = exit_status;
	ft_free_str_array(entry->env);
	entry->env = upd_env(exe, env);
	free_exe(exe);
	return (1);
}
