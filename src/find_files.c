/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:49:36 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/28 09:37:41 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_files(t_entry *entry, t_exe *exe, t_token *token)
{
	t_files	*new;

	new = files_new(entry, exe, token);
	files_addback(&(exe->files), new);
}
