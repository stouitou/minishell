/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:49:36 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/17 13:02:34 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_infiles(t_entry *entry, t_exe *exe, t_token *token)
{
	t_infile	*new;

	new = infile_new(entry, exe, token->content);
	infile_addback(&(exe->infile), new);
}

