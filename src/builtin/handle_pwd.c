/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:29:32 by poriou            #+#    #+#             */
/*   Updated: 2024/06/05 17:38:28 by stouitou         ###   ########.fr       */
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
			free_subshell_and_exit(exe, strerror(errno), "getcwd", 1);
		break ;
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
}
