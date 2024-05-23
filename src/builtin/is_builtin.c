/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:16:53 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/23 11:03:54 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		return (true);
	if (ft_strcmp(command, "env") == 0)
		return (true);
	return (false);
}
