/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:48:27 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 17:34:24 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key_for_export(t_exe *exe, char *arg)
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
		free_subshell_and_exit(exe, ERR_MALLOC, arg, EXIT_FAILURE);
	return (key);
}

char	*extract_value_for_export(t_exe *exe, char *arg)
{
	char	*value;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (NULL);
	value = ft_strdup(arg + i + 1);
	if (!value)
		free_subshell_and_exit(exe, ERR_MALLOC, arg, EXIT_FAILURE);
	return (value);
}

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

void	upd_concatenating(t_exe *exe, t_env *env, char *key, char *value)
{
	t_env	*relevant;
	char	*new;

	relevant = find_key_in_env(env, key);
	new = ft_strjoin(relevant->value, value);
	if (!new)
		free_subshell_and_exit(exe, ERR_MALLOC, value, EXIT_FAILURE);
	free(relevant->value);
	relevant->value = NULL;
	relevant->value = new;
}

void	upd_replacing(t_exe *exe, t_env *env, char *key, char *value)
{
	t_env	*relevant;
	char	*new;

	relevant = find_key_in_env(env, key);
	new = ft_strdup(value);
	if (!new)
		free_subshell_and_exit(exe, ERR_MALLOC, value, EXIT_FAILURE);
	free(relevant->value);
	relevant->value = NULL;
	relevant->value = new;
}
