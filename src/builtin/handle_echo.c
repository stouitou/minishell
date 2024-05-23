/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:37:38 by poriou            #+#    #+#             */
/*   Updated: 2024/05/23 12:10:13 by poriou           ###   ########.fr       */
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

void	handle_echo(t_entry *entry, t_exe *exe, char **cmd)
{
	int		i;
	bool	option;
	int		fd;

	(void)entry;
	option = get_newline_option(cmd[1]);
	if (!get_files_fd_for_exit(exe, exe->files))
		exit (1);
	if (exe->io_fd[1] != -1)
		fd = exe->io_fd[1];
	else
		fd = 1;
	i = 1;
	if (option)
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', fd);
}
