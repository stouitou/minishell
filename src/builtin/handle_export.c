/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:49:42 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/24 16:39:58 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_key(t_exe *exe, char *arg)
{
	char	*key;
	int		i;
	
	if (!arg)
		return (NULL);
	i = 0;
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (arg[i] != '=' || (arg[i] == '+' && arg[i + 1] != '=') || !i)
	{
		init_error(exe, "not a valid identifier", arg, 1);
		exit_builtin(exe, "export");
	}
	key = ft_strndup(arg, i);
	if (!key)
	{
		init_error(exe, strerror(errno), arg, EXIT_FAILURE);
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

static void	change_value(t_exe *exe, t_env *cur, char *arg, char *value)
{
	int		i;
	char	*new;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i - 1] == '+')
	{
		new = ft_strjoin(cur->value, value);
		if (!new)
		{
			init_error(exe, ERR_MALLOC, value, EXIT_FAILURE);
			free_subshell_and_exit(exe);
		}
	}
	else
	{
		new = ft_strdup(value);
		if (!new)
		{
			init_error(exe, ERR_MALLOC, value, EXIT_FAILURE);
			free_subshell_and_exit(exe);
		}
	}
	free(cur->value);
	cur->value = new;
}

static bool	exists_in_env(t_exe *exe, char *arg, char *key, char *value)
{
	t_env	*cur;

	cur = exe->env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			change_value(exe, cur, arg, value);
			return (true);
		}
		cur = cur->next;
	}
	return (false);
}

void	handle_export(t_exe *exe, char **cmd, t_env *env)
{
	int		ac;
	char	*key;
	char	*value;
	t_env	*new;
	
	if (!cmd || !env || !ft_strchr(cmd[1], '='))
		return ;
	ac = ft_str_array_len(cmd);
	if (ac != 2)
		return ;
	key = extract_key(exe, cmd[1]);
	value = extract_value(exe, cmd[1]);
	if (exists_in_env(exe, cmd[1], key, value))
		return ;
	new = env_new(key, value);
	if (!new)
	{
		init_error(exe, ERR_MALLOC, value, EXIT_FAILURE);
		free_subshell_and_exit(exe);
	}
	env_addback(&env, new);
	// print_env(env);
}
