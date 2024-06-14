/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:29:32 by poriou            #+#    #+#             */
/*   Updated: 2024/06/14 17:32:54 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pwd(t_exe *exe)
{
	char	*pwd;
	char	*buf;
	int		size;

	buf = NULL;
	size = 0;
	while (1)
	{
		pwd = getcwd(buf, size);
		if (!pwd && errno == ERANGE)
		{
			size++;
			continue ;
		}
		else if (!pwd)
		{
			pwd = ft_getenv(exe->env, "PWD");
			if (!pwd)
				free_subshell_and_exit(exe, strerror(errno), "getcwd", 1);
		}
		break ;
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	pwd = NULL;
}
