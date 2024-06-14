/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset_in_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:07:29 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 17:33:18 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_env *cur)
{
	free(cur->key);
	cur->key = NULL;
	free(cur->value);
	cur->value = NULL;
	free(cur);
	cur = NULL;
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

bool	handle_unset_in_parent(t_entry *ent, t_exe *exe, t_env *env, char **cmd)
{
	int		exit_status;
	int		i;

	if (!get_files_fd_for_builtin(exe, exe->files, "unset"))
	{
		free_exe(exe);
		ent->status = 1;
		return (true);
	}
	exit_status = 0;
	i = 1;
	while (cmd[i])
	{
		remove_variable(env, cmd[i]);
		i++;
	}
	ent->status = exit_status;
	ft_free_str_array(ent->env);
	ent->env = upd_env(exe, env);
	free_exe(exe);
	return (true);
}
