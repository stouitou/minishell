/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poriou <poriou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:52:05 by poriou            #+#    #+#             */
/*   Updated: 2024/05/28 11:24:59 by poriou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cd(t_exe *exe, char **cmd)
{
	char	*old_path;
	char	*path;

	path = NULL;
	if (ft_str_array_len(cmd) > 2)
	{
		init_error(exe, "too many arguments", "cd", EXIT_FAILURE);
		free_subshell_and_exit(exe);
	}
	old_path = getenv("OLDPWD");
	if (!cmd[1])
	{
		path = getenv("HOME");
		if (chdir(path) == -1)
			perror("chdir");
	}
}
