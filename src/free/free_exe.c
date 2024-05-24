/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:24:37 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/24 11:25:50 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exe(t_exe *exe)
{
	env_clear(&(exe->env));
	files_clear(&(exe->files));
	exe->files = NULL;
	free_cmd(exe->cmd);
}
