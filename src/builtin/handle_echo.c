/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:37:38 by poriou            #+#    #+#             */
/*   Updated: 2024/06/11 11:45:26 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (true);
	return (false);
}

static int	get_newline_option(char **cmd, bool *option)
{
	int	i;

	if (!cmd[1])
		return (1);
	i = 1;
	while (is_n_option(cmd[i]))
	{
		*option = true;
		i++;
	}
	return (i);
}

int	handle_echo(char **cmd)
{
	int		i;
	bool	option;

	option = false;
	i = get_newline_option(cmd, &option);
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
