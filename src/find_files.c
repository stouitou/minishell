/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:49:36 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/16 15:22:49 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_infiles(t_exe *exe, t_entry *entry, t_token *token, int count)
{
	char	**files;
	int		block;
	int		i;

	files = (char **)malloc((count + 1) * sizeof(char *));
	if (!files)
	{
		free_exe(exe);
		free_token_and_exit(&(entry->token), ERR_MALLOC, NULL, 1);
	}
	block = token->block;
	i = 0;
	while (token && token->block == block)
	{
		if (token->category == INFILE)
		{
			files[i] = ft_strdup(token->content);
			if (!files[i])
			{
				free_exe(exe);
				free_token_and_exit(&(entry->token), ERR_MALLOC, NULL, 1);
			}
			i++;
		}
		token = token->next;
	}
	files[i] = NULL;
	return (files);
}

static t_outfile	*find_outfiles(t_exe *exe, t_entry *entry, t_token *token)
{
	t_outfile	*new;
	t_outfile	*outfiles;
	int			block;

	outfiles = NULL;
	block = token->block;
	while (token && token->block == block)
	{
		if (token->category == OUTFILE || token->category == APP_OUTFILE)
		{
			new = outfile_new(entry, exe, token);
			outfile_addback(&outfiles, new);
		}
		token = token->next;
	}
	return (outfiles);
}

void	find_files(t_exe *exe, t_entry *entry, t_token *token, int count)
{
	exe->infile = find_infiles(exe, entry, token, count);
	exe->outfile = find_outfiles(exe, entry, token);
}

