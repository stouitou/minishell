/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:30:07 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 11:52:43 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	t_env	*cur;
	int		i;

	cur = env;
	i = 0;
	while (cur)
	{
		ft_printf("[%d] \033[32m%s\033[0m = %?33s\n", i, cur->key, cur->value);
		cur = cur->next;
		i++;
	}
}
