/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:15:22 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/30 15:34:14 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**init_cmd(t_entry *entry, t_token *token)
{
	t_token	*tmp;
	char	**cmd;
	int		block;
	int		elems;

	block = token->block;
	tmp = token;
	elems = 0;
	while (tmp && tmp->block == block)
	{
		if (tmp->category == CMD
			|| tmp->category == ARG
			|| tmp->category == OPTION)
			elems++;
		tmp = tmp->next;
	}
	cmd = (char **)malloc(sizeof(char *) * (elems + 1));
	if (!cmd)
		free_token_and_exit(&(entry->token), ERR_MALLOC, NULL, EXIT_FAILURE);
	return (cmd);
}

void	upd_exe(t_entry *entry, t_exe *exe, t_token *token, int i)
{
	int	j;

	j = 0;
	while (token && token->block < i)
		token = token->next;
	while (token && token->block == i)
	{
		if (token->category == INFILE)
			exe->infile = token->content;
		else if (token->category == OUTFILE)
			exe->outfile = token->content;
		else if (token->category == CMD || token->category == OPTION
			|| token->category == ARG)
		{
			if (token->category == CMD)
				exe->cmd = init_cmd(entry, token);
			exe->cmd[j] = ft_strdup(token->content);
			if (!exe->cmd[j])
			{
				free_cmd(exe->cmd);
				free_token_and_exit(&(entry->token), ERR_MALLOC, token->content, EXIT_FAILURE);
			}
			j++;
		}
		token = token->next;
	}
	exe->cmd[j] = NULL;
}
