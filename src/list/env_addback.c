/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:16:37 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/24 11:21:26 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_addback(t_env **env, t_env *new)
{
	t_env	*cur;
	
	if (!env || !new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	cur = *env;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
