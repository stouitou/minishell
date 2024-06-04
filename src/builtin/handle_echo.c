/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:37:38 by poriou            #+#    #+#             */
/*   Updated: 2024/05/28 13:21:22 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_newline_option(char *arg)
{
	if (!arg)
		return (false);
	if (ft_strcmp(arg, "-n") == 0)
		return (true);
	return (false);
}

int	handle_echo(char **cmd)
{
	int		i;
	bool	option;

	option = get_newline_option(cmd[1]);
	i = 1;
	if (option)
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', 1);
	return (0);
}
