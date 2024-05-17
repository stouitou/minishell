/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:24:37 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/17 13:04:31 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exe(t_exe *exe)
{
	infile_clear(&(exe->infile));
	exe->infile = NULL;
	outfile_clear(&(exe->outfile));
	exe->outfile = NULL;
	free_cmd(exe->cmd);
}
