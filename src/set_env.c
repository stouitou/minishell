/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:46:16 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/05 15:12:04 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_key(t_entry *entry, char *str)
{
	char	*key;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_strndup(str, i);
	if (!key)
		free_token_and_exit(entry, ERR_MALLOC, str, EXIT_FAILURE);
	return (key);
}

static char	*extract_value(t_entry *entry, char *str)
{
	char	*value;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	value = ft_strdup(str + i + 1);
	if (!value)
		free_token_and_exit(entry, ERR_MALLOC, str, EXIT_FAILURE);
	return (value);
}

void	set_env(t_entry *entry, t_exe *exe)
{
	t_env	*env;
	t_env	*new;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	i = 0;
	while (entry->env[i])
	{
		key = extract_key(entry, entry->env[i]);
		value = extract_value(entry, entry->env[i]);
		new = env_new(key, value);
		if (!new)
			free_token_and_exit(entry, ERR_MALLOC, entry->env[i], EXIT_FAILURE);
		env_addback(&env, new);
		i++;
	}
	exe->env = env;
}
