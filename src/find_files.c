/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:49:36 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/15 16:52:08 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_files(t_exe *exe, t_entry *entry, t_token *token, int cat)
{
	char	**files;
	int		nb;
	int		block;
	int		j;

	if (cat == INFILE)
		nb = exe->ioa_cnt[0];
	if (cat == OUTFILE)
		nb = exe->ioa_cnt[1];
	if (cat == APP_OUTFILE)
		nb = exe->ioa_cnt[2];
	files = (char **)malloc((nb + 1) * sizeof(char *));
	if (!files)
	{
		free_exe(exe);
		free_token_and_exit(&(entry->token), ERR_MALLOC, NULL, 1);
	}
	block = token->block;
	j = 0;
	while (token && token->block == block)
	{
		if (token->category == cat)
		{
			files[j] = ft_strdup(token->content);
			if (!files[j])
			{
				free_exe(exe);
				free_token_and_exit(&(entry->token), ERR_MALLOC, NULL, 1);
			}
			j++;
		}
		token = token->next;
	}
	files[j] = NULL;
	return (files);
}

void	find_all_files(t_exe *exe, t_entry *entry, t_token *token)
{
	exe->infile = find_files(exe, entry, token, INFILE);
	exe->outfile = find_files(exe, entry, token, OUTFILE);
	exe->app_outfile = find_files(exe, entry, token, APP_OUTFILE);
}

