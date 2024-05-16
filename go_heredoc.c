/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:36:51 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 17:37:07 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_heredoc(t_exe *exe, char *delimiter)
{
	t_heredoc	*heredoc;
	t_heredoc	*new;
	char		*str;

	while (1)
	{
		str = readline(H_PROMPT);
		if (ft_strcmp(str, delimiter) == 0)
			break ;
		new = heredoc_new(exe, str);
		heredoc_addback(&heredoc, new);
	}
	exe->heredoc = heredoc;
}
