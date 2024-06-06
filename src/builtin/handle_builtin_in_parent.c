/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_in_parent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:46:47 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/05 17:36:06 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_builtin_in_parent(t_entry *ent, t_exe *ex, t_env *env, char **cm)
{
	if (!cm || ex->blocks > 1)
		return (false);
	if (ft_strcmp(cm[0], "exit") == 0)
		return (handle_exit_in_parent(ent, ex, cm));
	else if (ft_strcmp(cm[0], "export") == 0)
		return (handle_export_in_parent(ent, ex, env, cm));
	else if (ft_strcmp(cm[0], "cd") == 0)
		return (handle_cd_in_parent(ent, ex, env, cm));
	else if (ft_strcmp(cm[0], "unset") == 0)
		return (handle_unset_in_parent(ent, ex, env, cm));
	return (false);
}
