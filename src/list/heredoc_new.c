/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:26:48 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 17:36:24 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*heredoc_new(t_exe *exe, char *content)
{
	t_heredoc	*new;

	new = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!new)
	{
		init_error(exe, ERR_MALLOC, content, EXIT_FAILURE);
		free_subshell_and_exit(exe);
	}
	new->content = ft_strdup(content);
	if (!new->content)
	{
		init_error(exe, ERR_MALLOC, content, EXIT_FAILURE);
		free_subshell_and_exit(exe);
	}
	new->next = NULL;
}
