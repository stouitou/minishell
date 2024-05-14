/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_subshell_and_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:24:37 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/14 11:31:03 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_subshell_and_exit(t_exe *exe)
{
	close_all_fd(exe);
	// if (ft_strcmp(exe->error.msg, ERR_CMD) == 0
	// 	|| ft_strcmp(exe->error.msg, ERR_PERM) == 0)
	// 	exe->error.data = exe->cmd[0];
	if (exe->error.msg)
		ft_fprintf(2, "%s", exe->error.msg);
	if (exe->error.data)
		ft_fprintf(2, ": %s", exe->error.data);
	if (exe->error.msg)
		ft_fprintf(2, "\n");
	// free_exe(exe);
	// ft_printf("exe->error.msg = %s\n", exe->error.msg);
	// ft_printf("exe->error.data = %s\n", exe->error.data);
	// ft_printf("exe->error.status = %d\n", exe->error.status);
	// if (ft_strcmp(exe->error.msg, ERR_MALLOC) == 0)
	// 	token_clear(&(entry->token));
	exit(exe->error.status);
}

// void	free_subshell_and_exit(t_exe *exe, t_entry *entry, char *error, int status)
// {
// 	char	*str;

// 	str = NULL;
// 	close_all_fd(exe);
// 	if (ft_strcmp(error, ERR_CMD) == 0
// 		|| ft_strcmp(error, ERR_PERM) == 0)
// 		str = exe->cmd[0];
// 	ft_fprintf(2, "%s", strerror(errno));
// 	if (error)
// 		ft_fprintf(2, ": %s", error);
// 	// if (str)
// 	// 	ft_fprintf(2, ": %s", str);
// 	ft_fprintf(2, "\n");
// 	free_cmd(exe->cmd);
// 	token_clear(&(entry->token));
// 	exit(status);
// }
