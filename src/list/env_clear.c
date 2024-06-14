/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:20:41 by stouitou          #+#    #+#             */
/*   Updated: 2024/06/14 17:35:14 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_clear(t_env **env)
{
	t_env	*cur;
	t_env	*next;

	if (!env)
		return ;
	cur = *env;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		cur->key = NULL;
		free(cur->value);
		cur->value = NULL;
		free(cur);
		cur = NULL;
		cur = next;
	}
	*env = NULL;
}
