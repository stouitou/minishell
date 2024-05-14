/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:20:02 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/16 12:22:39 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int	i;

	if (!env || !*env)
		return ;
	i = 0;
	while (env[i])
	{
		ft_printf("env[%d]: %s\n", i, env[i]);
		i++;
	}
}
