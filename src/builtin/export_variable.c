/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:29:31 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/04 15:51:27 by poriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	export_variable(t_exe *exe, t_env *env, char *var, int *status)
{
	char	*key;
	char	*value;
	t_env	*new;

	if (syntax_error_in_export(var, status))
		return ;
	key = extract_key_for_export(exe, var);
	value = extract_value_for_export(exe, var);
	if (exists_in_env(exe, key))
	{
		if (addition_operator(var))
			upd_concatenating(exe, env, key, value);
		else
			upd_replacing(exe, env, key, value);
		return ;
	}
	new = env_new(key, value);
	if (!new)
		free_subshell_and_exit(exe, ERR_MALLOC, value, EXIT_FAILURE);
	env_addback(&env, new);
}
