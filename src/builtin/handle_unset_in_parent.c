/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset_in_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:07:29 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 11:41:27 by stouitou         ###   ########.fr       */
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

	if (!env || !arg)
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

int	handle_unset_in_parent(t_entry *entry, t_exe *exe, t_env *env, char **cmd)
{
	int		exit_status;
	int		i;

	if (!cmd || exe->blocks > 1 || ft_strcmp(cmd[0], "unset") != 0)
		return (0);
	if (!get_files_fd_for_exit(exe, exe->files))
	{
		free_exe(exe);
		entry->status = 1;
		return (1);
	}
	exit_status = 0;
	i = 1;
	while (cmd[i])
	{
		remove_variable(env, cmd[i]);
		i++;
	}
	entry->status = exit_status;
	ft_free_str_array(entry->env);
	entry->env = upd_env(exe, env);
	free_exe(exe);
	return (1);
}
