/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:49:42 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/23 12:36:53 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_export(t_entry *entry, t_exe *exe, char **cmd, char **env)
{
	int		ac;
	
	(void)entry;
	(void)exe;
	(void)env;
	ac = ft_str_array_len(cmd);
	if (ac != 2)
		return ;
}
