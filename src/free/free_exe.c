/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:24:37 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 17:40:01 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exe(t_exe *exe)
{
	free_cmd(exe->infile);
	outfile_clear(&(exe->outfile));
	exe->outfile = NULL;
	heredoc_clear(&(exe->heredoc));
	exe->heredoc = NULL;
	free_cmd(exe->cmd);
}
