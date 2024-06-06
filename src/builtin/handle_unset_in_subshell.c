/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset_in_subshell.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:07:29 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/06 10:06:25 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	handle_unset_in_subshell(t_exe *exe, char **cmd, t_env *env)
{
	int		i;

	if (!env)
		return (1);
	if (!get_files_fd_for_builtin(exe, exe->files, "unset"))
	{
		free_exe(exe);
		return (1);
	}
	i = 1;
	while (cmd[i])
	{
		remove_variable(env, cmd[i]);
		i++;
	}
	return (0);
}
