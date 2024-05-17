/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:49:36 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/17 13:02:47 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_outfiles(t_entry *entry, t_exe *exe, t_token *token)
{
	t_outfile	*new;

	new = outfile_new(entry, exe, token);
	outfile_addback(&(exe->outfile), new);
}

